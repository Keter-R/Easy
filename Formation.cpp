#include "Formation.h"
#include <QBuffer>
#include <QPainter>
#include <QPainterPath>

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

QImage DataFormation::toQImage(QString raw)
{
	if(raw.isEmpty())
		return QImage();
	QByteArray array = QByteArray::fromBase64(raw.toUtf8());
	QImage image;
	image.loadFromData(array);
	return image;
}

QString DataFormation::toQString(QImage image)
{
	QByteArray array;
	QBuffer buffer(&array);
	buffer.open(QIODevice::WriteOnly);
	image.save(&buffer, "PNG");
	return array.toBase64();
}

QImage DataFormation::User::getRoundAvatar(int radius)
{
	QImage avatar = toQImage(this->avatar);
	QImage image = avatar.scaled(radius * 2, radius * 2, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
	QPainter painter(&image);
	painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
	QPainterPath path;
	path.addEllipse(0, 0, radius * 2, radius * 2);
	painter.setClipPath(path);
	painter.drawPixmap(0, 0, radius * 2, radius * 2, QPixmap::fromImage(avatar));
	return image;
}