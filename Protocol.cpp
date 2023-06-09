#include "Protocol.h"

using namespace DataFormation;

RawSolution::Protocol* RawSolution::Protocol::instance = new Protocol();

RawSolution::Protocol::Protocol()
{
	dbLnk = QSqlDatabase::addDatabase("QMYSQL");
	dbLnk.setDatabaseName("easy");
	dbLnk.setHostName("localhost");
	dbLnk.setUserName("root");
	dbLnk.setPassword("hfut123456");
	dbLnk.setPort(3306);
	dbLnk.open();
}

RawSolution::Protocol* RawSolution::Protocol::Instance()
{
	return instance;
}

bool RawSolution::Protocol::checkConnection()
{
	return dbLnk.isOpen();
}

bool RawSolution::Protocol::login(QString account, QString password)
{
	QSqlQuery query(dbLnk);
	query.prepare("select * from user where account = :account and password = :password");
	query.bindValue(":account", account);
	query.bindValue(":password", password);
	query.exec();
	return query.next();
}

User RawSolution::Protocol::getUser(QString account)
{
	QSqlQuery query(dbLnk);
	query.prepare("select * from user where account = :account");
	query.bindValue(":account", account);
	query.exec();
	query.next();
	User user;
	user.name = query.value(0).toString();
	user.account = query.value(1).toString();
	user.password = query.value(2).toString();
	user.friends = toAccountSet(query.value(3).toString());
	user.groups = toAccountSet(query.value(4).toString());
	user.avatar = query.value(5).toString();
	return user;
}

ChatRoom RawSolution::Protocol::getChatRoom(QString roomId)
{
	QSqlQuery query(dbLnk);
	query.prepare("select * from chatroom where roomId = :roomId");
	query.bindValue(":roomId", roomId);
	query.exec();
	query.next();
	ChatRoom chatRoom;
	chatRoom.name = query.value(0).toString();
	chatRoom.roomId = query.value(1).toString();
	chatRoom.members = toAccountSet(query.value(2).toString());
	return chatRoom;
}

QVector<Message> RawSolution::Protocol::getRoomMessages(QString roomId)
{
	QSqlQuery query(dbLnk);
	query.prepare("select * from message where receiver = :receiver");
	query.bindValue(":receiver", roomId);
	query.exec();
	QVector<Message> messages;
	while (query.next())
	{
		Message msg;
		msg.sender = query.value(0).toString();
		msg.receiver = query.value(1).toString();
		msg.content = query.value(2).toString();
		msg.time = query.value(3).toString();
		messages.push_back(msg);
	}
	std::sort(messages.begin(), messages.end(), [](Message a, Message b) {return a.time < b.time; });
	return messages;
}

QVector<Message> RawSolution::Protocol::getBiMessages(QString userAccount, QString friendAccount)
{
	QSqlQuery query(dbLnk);
	query.prepare("select * from message where (sender = :sender and receiver = :receiver) or (sender = :receiver and receiver = :sender)");
	query.bindValue(":sender", userAccount);
	query.bindValue(":receiver", friendAccount);
	query.exec();
	QVector<Message> messages;
	while (query.next())
	{
		Message msg;
		msg.sender = query.value(0).toString();
		msg.receiver = query.value(1).toString();
		msg.content = query.value(2).toString();
		msg.time = query.value(3).toString();
		messages.push_back(msg);
	}
	std::sort(messages.begin(), messages.end(), [](Message a, Message b) {return a.time < b.time; });
	return messages;
}

void RawSolution::Protocol::addMessage(Message msg)
{
	QSqlQuery query(dbLnk);
	query.prepare("insert into message values(:sender, :receiver, :content, :time)");
	query.bindValue(":sender", msg.sender);
	query.bindValue(":receiver", msg.receiver);
	query.bindValue(":content", msg.content);
	query.bindValue(":time", msg.time);
	query.exec();
}

void RawSolution::Protocol::addFriend(QString account, QString friendAccount)
{
	QSqlQuery query(dbLnk);
	User a = getUser(account);
	User b = getUser(friendAccount);
	a.friends.insert(friendAccount);
	b.friends.insert(account);
	query.prepare("update user set friends = :friends where account = :account");
	query.bindValue(":friends", toQString(a.friends));
	query.bindValue(":account", account);
	query.exec();
	query.prepare("update user set friends = :friends where account = :account");
	query.bindValue(":friends", toQString(b.friends));
	query.bindValue(":account", friendAccount);
	query.exec();
}

void RawSolution::Protocol::addChatRoom(QString hostAccount, DataFormation::ChatRoom chatRoom)
{
	QSqlQuery query(dbLnk);
	query.prepare("insert into chatroom values(:name, :roomId, :members)");
	query.bindValue(":name", chatRoom.name);
	query.bindValue(":roomId", chatRoom.roomId);
	query.bindValue(":members", toQString(chatRoom.members));
	auto res = query.exec();
	User user = getUser(hostAccount);
	user.groups.insert(chatRoom.roomId);
	query.prepare("update user set user.groups = :groups where account = :account");
	query.bindValue(":groups", toQString(user.groups));
	query.bindValue(":account", user.account);
	query.exec();
}

void RawSolution::Protocol::removeFriend(QString account, QString friendAccount)
{
	QSqlQuery query(dbLnk);
	User a = getUser(account);
	User b = getUser(friendAccount);
	a.friends.remove(friendAccount);
	b.friends.remove(account);
	query.prepare("update user set friends = :friends where account = :account");
	query.bindValue(":friends", toQString(a.friends));
	query.bindValue(":account", account);
	query.exec();
	query.prepare("update user set friends = :friends where account = :account");
	query.bindValue(":friends", toQString(b.friends));
	query.bindValue(":account", friendAccount);
	query.exec();
}

void RawSolution::Protocol::joinChatRoom(QString account, QString roomId)
{
	QSqlQuery query(dbLnk);
	ChatRoom chatRoom = getChatRoom(roomId);
	chatRoom.members.insert(account);
	User user = getUser(account);
	user.groups.insert(roomId);
	query.prepare("update user set user.groups = :groups where account = :account");
	query.bindValue(":groups", toQString(user.groups));
	query.bindValue(":account", account);
	query.exec();
	query.prepare("update chatroom set members = :members where roomId = :roomId");
	query.bindValue(":members", toQString(chatRoom.members));
	query.bindValue(":roomId", roomId);
	query.exec();
}

void RawSolution::Protocol::quitChatRoom(QString account, QString roomId)
{
	QSqlQuery query(dbLnk);
	ChatRoom chatRoom = getChatRoom(roomId);
	chatRoom.members.remove(account);
	User user = getUser(account);
	user.groups.remove(roomId);
	query.prepare("update user set groups = :groups where account = :account");
	query.bindValue(":groups", toQString(user.groups));
	query.bindValue(":account", account);
	query.exec();
	query.prepare("update chatroom set members = :members where roomId = :roomId");
	query.bindValue(":members", toQString(chatRoom.members));
	query.bindValue(":roomId", roomId);
	query.exec();
}

void RawSolution::Protocol::changeAvatar(QString account, QImage avatar)
{
	QSqlQuery query(dbLnk);
	User user = getUser(account);
	user.avatar = toQString(avatar);
	query.prepare("update user set user.avatar = :avatar where account = :account");
	query.bindValue(":avatar", toQString(avatar));
	query.bindValue(":account", account);
	query.exec();
}