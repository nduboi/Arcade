/*
** EPITECH PROJECT, 2025
** arcade
** File description:
** ArcadeCanvas
*/

#include "ArcadeCanvas.hpp"

QString loadArcadeFont();

ArcadeCanvas::ArcadeCanvas(QWidget *parent) : QWidget(parent) {
    setAttribute(Qt::WA_OpaquePaintEvent);
    setAttribute(Qt::WA_NoSystemBackground);
    setAutoFillBackground(false);
}

void ArcadeCanvas::addRectangle(const QRect& rect, const QColor& color) {
    DrawCommand cmd;
    cmd.type = DrawCommand::RECTANGLE;
    cmd.rect = rect;
    cmd.color = color;
    _commands.push_back(cmd);
}

void ArcadeCanvas::addText(const QString& text, const QPoint& pos, const QColor& color, const QColor& outlineColor, int fontSize) {
    DrawCommand cmd;
    cmd.type = DrawCommand::TEXT;
    cmd.rect = QRect(pos, QSize(1000, fontSize + 5));
    cmd.color = color;
    cmd.outlineColor = outlineColor;
    cmd.text = text.toStdString();
    cmd.fontSize = fontSize;
    _commands.push_back(cmd);
}

void ArcadeCanvas::addSprite(const QString& imagePath, const QRect& rect) {
    DrawCommand cmd;
    cmd.type = DrawCommand::SPRITE;
    cmd.rect = rect;
    cmd.imagePath = imagePath.toStdString();
    _commands.push_back(cmd);
}

void ArcadeCanvas::addThickRectangle(const QRect& rect, int thickness) {
    DrawCommand cmd;
    cmd.type = DrawCommand::THICK_RECTANGLE;
    cmd.rect = rect;
    cmd.thickness = thickness;
    _commands.push_back(cmd);
}

void ArcadeCanvas::clear() {
    _commands.clear();
    update();
}


void ArcadeCanvas::paintEvent(QPaintEvent* event) {
    QPainter painter(this);
    painter.fillRect(rect(), Qt::black);

    QString fontFamily = loadArcadeFont();

    for (const auto& cmd : _commands) {
        switch (cmd.type) {
            case DrawCommand::RECTANGLE:
                painter.setPen(Qt::NoPen);
                painter.setBrush(cmd.color);
                painter.drawRect(cmd.rect);
                break;

            case DrawCommand::TEXT: {
                QFont font(fontFamily, cmd.fontSize * 0.7);
                painter.setFont(font);

                if (cmd.outlineColor.isValid()) {
                    painter.setPen(cmd.outlineColor);
                    for (int dx = -1; dx <= 1; dx++) {
                        for (int dy = -1; dy <= 1; dy++) {
                            if (dx != 0 || dy != 0) {
                                painter.drawText(cmd.rect.adjusted(dx, dy, dx, dy),
                                                 Qt::AlignLeft | Qt::AlignTop,
                                                 QString::fromStdString(cmd.text));
                            }
                        }
                    }
                }

                painter.setPen(cmd.color);
                painter.drawText(cmd.rect, Qt::AlignLeft | Qt::AlignTop, QString::fromStdString(cmd.text));
                break;
            }

            case DrawCommand::SPRITE: {
                QPixmap pixmap(QString::fromStdString(cmd.imagePath));
                if (!pixmap.isNull()) {
                    if (cmd.rect.width() > width() / 2) {
                        pixmap = pixmap.scaled(width(), height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
                        painter.drawPixmap(0, 0, pixmap);
                    } else {
                        pixmap = pixmap.scaled(cmd.rect.size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
                        painter.drawPixmap(cmd.rect.topLeft(), pixmap);
                    }
                } else {
                    painter.fillRect(cmd.rect, QColor(255, 0, 255));
                }
                break;
            }

            case DrawCommand::THICK_RECTANGLE: {
                painter.setPen(Qt::NoPen);
                painter.setBrush(Qt::white);
                painter.drawRect(cmd.rect);

                painter.setBrush(Qt::black);
                painter.drawRect(
                    cmd.rect.left() + cmd.thickness,
                    cmd.rect.top() + cmd.thickness,
                    cmd.rect.width() - 2 * cmd.thickness,
                    cmd.rect.height() - 2 * cmd.thickness
                );
                break;
            }
        }
    }
}
