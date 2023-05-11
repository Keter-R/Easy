#pragma once
#include "Formation.h"
#include <QSQL>
#include <QVector>
#include <QSqlDatabase>
#include <QSqlQuery>

namespace RawSolution
{
	class Protocol : public QObject
	{
		Q_OBJECT
		public:
			static Protocol* Instance();
			bool checkConnection();
			bool login(QString account, QString password);
			DataFormation::User getUser(QString account);
			DataFormation::ChatRoom getChatRoom(QString roomId);
			QVector<DataFormation::Message> getRoomMessages(QString roomId);
			QVector<DataFormation::Message> getBiMessages(QString userAccount, QString friendAccount);
			void addMessage(DataFormation::Message msg);
			void addFriend(QString account, QString friendAccount);
			void addChatRoom(QString hostAccount, DataFormation::ChatRoom chatRoom);
			void removeFriend(QString account, QString friendAccount);
			void removeChatRoom(QString roomId);
			void joinChatRoom(QString account, QString roomId);
			void quitChatRoom(QString account, QString roomId);
			void changeAvatar(QString account, QImage avatar);

		private:
			static Protocol* instance;
			Protocol();
			Protocol(const Protocol&) = delete;
			Protocol& operator=(const Protocol&) = delete;
			QSqlDatabase dbLnk;
	};
}


