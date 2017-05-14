#ifndef TURTLENODEEDITOR_H
#define TURTLENODEEDITOR_H

#include <QLineEdit>
#include <QTableView>

#include <QWidget>

#include <Presenter/Elements/Nodes/TurtleNodePresenter.h>

constexpr float FU_GEN_PI = 3.14159265359;

#include <iostream>

class ProductionModel : public QAbstractTableModel
{
	Q_OBJECT
	//
	signals:
	//
    void editCompleted(const QString &);
	//
private:
	//
	TurtleNodePresenter &Turtle;
	//
	std::vector<char> IndexingArray;
	//
	void RefreshIndexingArray()
	{
		IndexingArray.resize(Turtle.GetProductions().size());
		int i=0;
		for(auto &I : Turtle.GetProductions())
		{
			IndexingArray[i] = I.first;
			i++;
		}
	}
	//
public:
	//
	virtual int rowCount(const QModelIndex &parent = QModelIndex()) const override
	{
		return IndexingArray.size() + 1;
	}
	//
	virtual int columnCount(const QModelIndex &parent = QModelIndex()) const override
	{
		return 2;
	}
	//
	virtual Qt::ItemFlags flags(const QModelIndex &index) const override
	{
		return Qt::ItemIsEditable | QAbstractTableModel::flags(index);
	}
	//
	virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const override
	{
		if (role == Qt::DisplayRole)
		{
			if (orientation == Qt::Horizontal)
			{
				switch (section)
				{
				case 0:
					return QString("Predecessor");
				case 1:
					return QString("Successor");
				}
			}
		}
		return QVariant();
	}
	//
	virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override
	{
		if(role == Qt::DisplayRole || role == Qt::EditRole)
		{
			if(index.row() < IndexingArray.size())
			{
				if(index.column() == 0)
				{
					return QString(IndexingArray[index.row()]);
				}
				if(index.column() == 1)
				{
					return QString::fromStdString(Turtle.GetProductions().find(IndexingArray[index.row()])->second.GetSuccessor());
				}
			}
		}
		//
		return QVariant();
	}
	//
	virtual bool setData(const QModelIndex &index, const QVariant &value, int role) override
	{
		if (role == Qt::EditRole)
		{
			if(index.row() < IndexingArray.size())
			{
				if(index.column() == 0 && value.toString().size() == 1)
				{
					std::string SuccessorValue = Turtle.GetProductions().find(IndexingArray[index.row()])->second.GetSuccessor();
					Turtle.DeleteProduction(IndexingArray[index.row()]);
					IndexingArray[index.row()] = value.toString().at(0).toLatin1();
					Turtle.AddProduction(IndexingArray[index.row()],SuccessorValue);
					//
					emit editCompleted(value.toString());
				}
				else if (index.column() == 1)
				{
					Turtle.AddProduction(IndexingArray[index.row()],value.toString().toStdString());
					//
					emit editCompleted(value.toString());
				}
			}
			else
			{
				if(index.column() == 0 && value.toString().size() == 1)
				{
					char Predecessor = value.toString().at(0).toLatin1();
					if(!Turtle.HasProduction(Predecessor))
					{
						beginInsertRows(QModelIndex(),IndexingArray.size() + 2,IndexingArray.size() + 2);
						Turtle.AddProduction(value.toString().at(0).toLatin1(),"");
						RefreshIndexingArray();
						//
						emit editCompleted(value.toString());
						endInsertRows();
					}
				}
			}
		}
		return true;
	}
	//
	ProductionModel(TurtleNodePresenter &turtle)
		:Turtle(turtle)
	{
		RefreshIndexingArray();
	}
};

class TurtleNodeEditor : public QWidget
{
    Q_OBJECT

private:
	QLineEdit *DeltaDistance;
	QLineEdit *DeltaAngle;
	QLineEdit *Axiom;
	QLineEdit *RecursionDepth;
	QTableView *Productions;
	//
	TurtleNodePresenter *TurtleNode;
	//
	ProductionModel TableModel;
	//
private slots:
	//
	void DeltaDistanceChanged()
	{
		std::cout << "New distance " << DeltaDistance->text().toDouble() << std::endl;
		TurtleNode->SetDeltaDistance(DeltaDistance->text().toDouble());
	}
	//
	void DeltaAngleChanged()
	{
		std::cout << "New angle: " << DeltaAngle->text().toDouble() << std::endl;
		TurtleNode->SetDeltaAngle(DeltaAngle->text().toDouble() * FU_GEN_PI / 180.0);
	}
	//
	void AxiomChanged()
	{
		std::cout << "New axiom" << Axiom->text().toStdString() << std::endl;
		TurtleNode->SetAxiom(Axiom->text().toStdString());
	}
	//
	void RecursionDepthChanged()
	{
		std::cout << "New recursion depth" << RecursionDepth->text().toStdString() << std::endl;
		TurtleNode->SetRecursionDepth(RecursionDepth->text().toInt());
	}
	//
public:
	//
	TurtleNodeEditor(TurtleNodePresenter *turtle_node);
	//
	virtual ~TurtleNodeEditor() override;
};

#endif // TURTLENODEEDITOR_H
