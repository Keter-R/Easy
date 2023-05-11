#pragma once

#include<QString>
#include<QJsonObject>
#include<QJsonDocument>
#include<QJsonArray>
#include<QSet>
#include<QImage>


namespace DataFormation
{
	using AccountSet = QSet<QString>;

	AccountSet toAccountSet(QString raw);
	QString toQString(AccountSet set);
	QImage toQImage(QString raw);
	QString toQString(QImage image);

	struct User
	{
		QString avatar;
		QString name;
		QString account;
		QString password;
		AccountSet friends;
		AccountSet groups;
		QImage getRoundAvatar(int radius = 50);
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
		bool operator > (const Message& other) const;
		bool operator < (const Message& other) const;
	};

	struct MessageContent
	{
		QString type;
		QString content;
		QString fileLink;
		QString fileName;
	};


	MessageContent toMessageContent(QString raw);
	QString toQString(MessageContent content);
}