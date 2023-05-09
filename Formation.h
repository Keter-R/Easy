#pragma once

#include<QString>
#include<QJsonObject>
#include<QJsonDocument>
#include<QJsonArray>
#include<QSet>


namespace DataFormation
{
	using AccountSet = QSet<QString>;

	AccountSet toAccountSet(QString raw);
	QString toQString(AccountSet set);

	struct User
	{
		QString name;
		QString account;
		QString password;
		AccountSet friends;
		AccountSet groups;
	};

	struct ChatRoom
	{
		QString name;
		QString roomId;
		AccountSet members;
	};

	struct Message
	{
		QString sender;
		QString receiver;
		QString content;
		QString time;
	};
}