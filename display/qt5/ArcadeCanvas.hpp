/*
** EPITECH PROJECT, 2025
** arcade
** File description:
** ArcadeCanvas
*/

#ifndef ARCADECANVAS_HPP_
#define ARCADECANVAS_HPP_

#include <QApplication>
#include <QMainWindow>
#include <QWidget>
#include <QPainter>
#include <QEvent>
#include <QPixmap>
#include <vector>
#include <string>

class ArcadeCanvas : public QWidget {
    Q_OBJECT
public:
    explicit ArcadeCanvas(QWidget *parent = nullptr);

    struct DrawCommand {
        enum Type {
            RECTANGLE,
            TEXT,
            SPRITE,
            THICK_RECTANGLE
        };

        Type type;
        QRect rect;
        QColor color;
        QColor outlineColor;
        std::string text;
        std::string imagePath;
        int thickness;
        int fontSize;
    };

    void addRectangle(const QRect& rect, const QColor& color);
    void addText(const QString& text, const QPoint& pos, const QColor& color, const QColor& outlineColor, int fontSize);
    void addSprite(const QString& imagePath, const QRect& rect);
    void addThickRectangle(const QRect& rect, int thickness);
    void clear();

protected:
    void paintEvent(QPaintEvent* event) override;

private:
    std::vector<DrawCommand> _commands;
};

#endif /* !ARCADECANVAS_HPP_ */
