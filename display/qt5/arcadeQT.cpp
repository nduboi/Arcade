//
// Created by roussierenoa on 3/17/25.
//

#include <iostream>
#include "arcadeQT.hpp"
#include <QKeyEvent>
#include <QMouseEvent>
#include <QPainter>
#include <QFont>
#include <QFontDatabase>
#include <QCursor>
#include <QPaintEvent>

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

QString loadArcadeFont() {
    static bool fontLoaded = false;
    static QString fontFamily = "Arial";
    static QFontDatabase fontDb;

    fontLoaded = false;

    if (!fontLoaded) {
        int fontId = fontDb.addApplicationFont("assets/ARCADECLASSIC.TTF");
        if (fontId != -1) {
            QStringList families = fontDb.applicationFontFamilies(fontId);
            if (!families.isEmpty()) {
                fontFamily = families.at(0);
                fontLoaded = true;
            }
        }
    }

    return fontFamily;
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

arcadeQT::EventHandler::EventHandler(arcadeQT* parent) : QObject(nullptr), _arcade(parent) {}

bool arcadeQT::EventHandler::eventFilter(QObject *watched, QEvent *event)
{
    if (watched == _arcade->_window || watched == _arcade->_canvas) {
        if (event->type() == QEvent::KeyPress) {
            QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
            _arcade->_lastEvent.type = QEvent::KeyPress;
            _arcade->_lastEvent.key = keyEvent->key();
            _arcade->_lastEvent.processed = false;
            return true;
        }
        else if (event->type() == QEvent::MouseButtonPress) {
            QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
            _arcade->_lastEvent.type = QEvent::MouseButtonPress;
            _arcade->_lastEvent.mouseButton = mouseEvent->button();
            _arcade->_lastEvent.mouseX = mouseEvent->x();
            _arcade->_lastEvent.mouseY = mouseEvent->y();
            _arcade->_lastEvent.processed = false;
            return true;
        }
        else if (event->type() == QEvent::Close) {
            _arcade->_lastEvent.type = QEvent::Close;
            _arcade->_lastEvent.processed = false;
            return true;
        }
    }

    return QObject::eventFilter(watched, event);
}

void arcadeQT::display() {
    _app->processEvents();
    _canvas->update();
}

void arcadeQT::closeWindow() {
    if (_window) {
        _window->close();
        _isOpen = false;
    }
}

bool arcadeQT::isOpen() {
    return _isOpen;
}

void arcadeQT::clear() {
    if (_canvas) {
        _canvas->clear();
    }
}

std::pair<int, int> arcadeQT::_getWindowPosition(std::pair<int, int> position) {
    std::pair<int, int> windowPosition;
    QSize windowSize = _window->size();
    const int hudOffset = 100;

	std::cout << "Window size: " << windowSize.width() << ", " << windowSize.height() << std::endl;
	std::cout << "Position: " << position.first << ", " << position.second << std::endl;
    windowPosition.first = (position.first * windowSize.width()) / this->_mapSize.first;
    windowPosition.second = hudOffset + (position.second * (windowSize.height() - hudOffset)) / this->_mapSize.second;
    return windowPosition;
}

void arcadeQT::drawSprite(std::string asset, int color, std::string text, std::pair<size_t, size_t> position) {
    if (!_canvas)
        return;

    std::pair<int, int> windowPosition = this->_getWindowPosition(position);

    QSize windowSize = _window->size();
    int hudOffset = 100;
    int cellWidth = windowSize.width() / _mapSize.first;
    int cellHeight = (windowSize.height() - hudOffset) / _mapSize.second;

    QFile file(QString::fromStdString(asset));
    if (file.exists()) {
        _canvas->addSprite(
            QString::fromStdString(asset),
            QRect(windowPosition.first, windowPosition.second, cellWidth, cellHeight)
        );
    } else {
        drawRectangle(color, windowPosition);
    }
}

void arcadeQT::drawRectangle(int color, std::pair<size_t, size_t> position) {
    if (!_canvas)
        return;

    QColor fillColor;
    switch (color) {
        case 0: fillColor = Qt::black; break;
        case 1: fillColor = Qt::white; break;
        case 2: fillColor = Qt::red; break;
        case 3: fillColor = Qt::green; break;
        case 4: fillColor = Qt::blue; break;
        default: fillColor = Qt::black; break;
    }

    QSize windowSize = _window->size();
    int hudOffset = 100;
    int cellWidth = windowSize.width() / _mapSize.first;
    int cellHeight = (windowSize.height() - hudOffset) / _mapSize.second;

    _canvas->addRectangle(
        QRect(position.first, position.second, cellWidth, cellHeight),
        fillColor
    );
}

void arcadeQT::drawRectangleMenu(std::pair<size_t, size_t> size, std::pair<size_t, size_t> position, color_t color)
{
    if (!_canvas)
        return;

    _canvas->addRectangle(
        QRect(position.first, position.second, size.first, size.second),
        QColor(color.r, color.g, color.b)
    );
}

void arcadeQT::drawTextMenu(std::string text, std::pair<size_t, size_t> position, color_t color, int charSize)
{
    if (!_canvas)
        return;

    int adjustedSize = static_cast<int>(charSize * 1);

    _canvas->addText(
        QString::fromStdString(text),
        QPoint(position.first, position.second),
        QColor(color.r, color.g, color.b),
        QColor(),
        adjustedSize
    );
}

void arcadeQT::drawSpriteMenu(std::pair<float, float> size, std::string asset, std::pair<int, int> position)
{
    if (!_canvas)
        return;

    QFile file(QString::fromStdString(asset));
	_canvas->addSprite(
		QString::fromStdString(asset),
		QRect(0, 0, _window->width(), _window->height())
	);
}

void arcadeQT::drawThickRectangle(std::pair<int, int> position, std::pair<int, int> size, int thickness)
{
    if (!_canvas)
        return;

    _canvas->addThickRectangle(
        QRect(position.first, position.second, size.first, size.second),
        thickness
    );
}

std::pair<int, int> arcadeQT::getWindowSize() {
    if (!_window)
        return {0, 0};

    return {_window->width(), _window->height()};
}

bool arcadeQT::isMouseOver(std::pair<size_t, size_t> position, std::pair<size_t, size_t> size) {
    if (!_window)
        return false;

    QPoint mousePos = _window->mapFromGlobal(QCursor::pos());

    if (mousePos.x() >= static_cast<int>(position.first) &&
        mousePos.x() <= static_cast<int>(position.first + size.first) &&
        mousePos.y() >= static_cast<int>(position.second) &&
        mousePos.y() <= static_cast<int>(position.second + size.second)) {
        return true;
    }
    return false;
}

void arcadeQT::drawText(std::string text, int color, std::pair<size_t, size_t> position) {
    if (!_canvas)
        return;

    QColor textColor;
    QColor outlineColor;

    switch (color) {
        case 0:
            textColor = Qt::black;
            outlineColor = Qt::white;
            break;
        case 1:
            textColor = Qt::white;
            outlineColor = Qt::black;
            break;
        case 2:
            textColor = Qt::red;
            outlineColor = Qt::white;
            break;
        case 3:
            textColor = Qt::green;
            outlineColor = Qt::white;
            break;
        case 4:
            textColor = Qt::blue;
            outlineColor = Qt::white;
            break;
        default:
            textColor = Qt::black;
            outlineColor = Qt::white;
            break;
    }

    const int adjustedSize = 24;

    _canvas->addText(
        QString::fromStdString(text),
        QPoint(position.first, position.second),
        textColor,
        outlineColor,
        adjustedSize
    );
}

void arcadeQT::setMapSize(std::pair<size_t, size_t> size) {
    this->_mapSize = size;
}

void arcadeQT::resizeWindow(size_t x, size_t y) {
    if (_window) {
        _window->resize(x, y);
    }
}

arcadeQT::arcadeQT() : _isOpen(true)
{
    int argc = 0;

    _app = new QApplication(argc, nullptr);
    _window = new QMainWindow();
    _canvas = new ArcadeCanvas();
    _eventHandler = new EventHandler(this);
    loadArcadeFont();
    _window->setCentralWidget(_canvas);
    _window->installEventFilter(_eventHandler);
    _canvas->installEventFilter(_eventHandler);

    _window->setWindowTitle("Arcade - Qt5");
    _window->resize(1620, 900);
    _window->show();

    _mapSize = {0, 0};
}

arcadeQT::~arcadeQT() {
    delete _eventHandler;
    delete _window;
    delete _app;
    _eventHandler = nullptr;
    _window = nullptr;
    _canvas = nullptr;
    _app = nullptr;
}
