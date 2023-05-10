#include "FunctionalPage.h"
#include <QDialog>
#include <QInputDialog>
#include <QMessageBox>
#include <QPainter>
#include <QFileDialog>
#include <QMenu>
#include <QTimer>

FunctionalPage::FunctionalPage(DataFormation::User user, QWidget* parent)
	: QWidget(parent), currentUser(user)
{
	ui.setupUi(this);
	ui.username->setText("user name : "+ currentUser.name);
	ui.useraccount->setText("user account : "+ currentUser.account);
	this->refreshAvatar();
	connect(ui.joinfriend, &QPushButton::clicked, [=]() {
			QString friendAccount = QInputDialog::getText(this, "Add Friend", "Please input your friend's account");
			DataFormation::User friend_ = RawSolution::Protocol::Instance()->getUser(friendAccount);
			if (friend_.account == "")
			{
				QMessageBox::warning(this, "Add Friend Failed", "Account is wrong!");
			}
			else if (currentUser.friends.contains(friend_.account))
			{
				QMessageBox::warning(this, "Add Friend Failed", "You have already added this friend!");
			}
			else if (currentUser.account == friend_.account)
			{
				QMessageBox::warning(this, "Add Friend Failed", "You can't add yourself!");
			}
			else
			{
				RawSolution::Protocol::Instance()->addFriend(currentUser.account, friendAccount);
				QMessageBox::information(this, "Add Friend Success", "Add friend success!");
			}
		});
	connect(ui.joingroup, &QPushButton::clicked, [=]() {
			QString chatRoomId = QInputDialog::getText(this, "Join Chat Room", "Please input the chat room id");
			DataFormation::ChatRoom chatRoom = RawSolution::Protocol::Instance()->getChatRoom(chatRoomId);
			if (chatRoom.roomId == "")
			{
				QMessageBox::warning(this, "Join Chat Room Failed", "Chat room id is wrong!");
			}
			else if (currentUser.groups.contains(chatRoom.roomId))
			{
				QMessageBox::warning(this, "Join Chat Room Failed", "You have already joined this chat room!");
			}
			else
			{
				RawSolution::Protocol::Instance()->joinChatRoom(user.account, chatRoomId);
				QMessageBox::information(this, "Join Chat Room Success", "Join chat room success!");
			}
		});
	connect(ui.creategroup, &QPushButton::clicked, [=]() {
			QString chatRoomName = QInputDialog::getText(this, "Create Chat Room", "Please input the chat room name");
			DataFormation::ChatRoom chatRoom;
			qsrand(QTime::currentTime().msec());
			chatRoom.roomId = "R" + QString::number(1ull * qrand() * qrand() * qrand() % 100000);
			while (RawSolution::Protocol::Instance()->getChatRoom(chatRoom.roomId).roomId != "")
			{
				chatRoom.roomId = "R" + QString::number(1ull * qrand() * qrand() * qrand() % 100000);
			}
			chatRoom.name = chatRoomName;
			chatRoom.members.insert(currentUser.account);
			RawSolution::Protocol::Instance()->addChatRoom(currentUser.account, chatRoom);
			QMessageBox::information(this, "Create Chat Room Success", "Create chat room success!");

		});
}

FunctionalPage::~FunctionalPage()
{
}

void FunctionalPage::refreshAvatar()
{
	if (currentUser.avatar.isNull())
	{
		currentUser.avatar = DataFormation::toQString(QImage(":/Easy/src/icon/upload_image.svg"));
	}
	ui.avatarImage->setPixmap(QPixmap::fromImage(currentUser.getRoundAvatar(40)));
}

void FunctionalPage::changeAvatar(QImage img)
{
	currentUser.avatar = DataFormation::toQString(img);
	RawSolution::Protocol::Instance()->changeAvatar(currentUser.account, img);
	this->refreshAvatar();
}

void FunctionalPage::mousePressEvent(QMouseEvent* event)
{
	if (event->button() == Qt::RightButton)
	{
		// get avatar widget position range
		QPoint avatarPos = ui.avatar->mapToGlobal(QPoint(0, 0));
		QRect avatarRect = QRect(avatarPos, QSize(100, 100));
		// if mouse is in avatar widget
		if (avatarRect.contains(event->globalPos()))
		{
			// show menu
			QMenu* menu = new QMenu(this);
			QAction* changeAvatar = new QAction("Change Avatar", this);
			menu->addAction(changeAvatar);
			connect(changeAvatar, &QAction::triggered, [=]() {
					QString fileName = QFileDialog::getOpenFileName(this, "Open Image", ".", "Image Files(*.jpg *.png *.bmp)");
					if (fileName != "")
					{
						QImage img(fileName);
						this->changeAvatar(img);
					}
				});
			menu->exec(QCursor::pos());
		}

	}
}