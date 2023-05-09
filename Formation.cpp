#include "Formation.h"

using namespace DataFormation;

AccountSet DataFormation::toAccountSet(QString raw)
{
	AccountSet set;
	QJsonDocument doc = QJsonDocument::fromJson(raw.toUtf8());
	QJsonArray array = doc.array();
	for (auto i : array)
	{
		set.insert(i.toString());
	}
	return set;
}

QString DataFormation::toQString(AccountSet set)
{
	QJsonArray array;
	for (auto i : set)
	{
		array.append(i);
	}
	QJsonDocument doc(array);
	return doc.toJson();
}