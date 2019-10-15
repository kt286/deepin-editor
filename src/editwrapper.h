/*
 * Copyright (C) 2017 ~ 2018 Deepin Technology Co., Ltd.
 *
 * Author:     rekols <rekols@foxmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef EDITORBUFFER_H
#define EDITORBUFFER_H

#include "dbusinterface.h"
#include "dtextedit.h"
#include "widgets/bottombar.h"
#include "warningnotices.h"

#include <QVBoxLayout>
#include <QWidget>
#include <DMessageManager>
#include <DFloatingMessage>

class EditWrapper : public QWidget
{
    Q_OBJECT

public:
    // end of line mode.
    enum EndOfLineMode {
        eolUnknown = -1,
        eolUnix = 0,
        eolDos = 1,
        eolMac = 2
    };

    struct FileStateItem {
        QDateTime modified;
        QFile::Permissions permissions;
    };

    EditWrapper(QWidget *parent = 0);
    ~EditWrapper();

    void openFile(const QString &filepath);
    bool saveFile();
    void updatePath(const QString &file);
    void refresh();
    bool isLoadFinished() { return m_isLoadFinished; }

    EndOfLineMode endOfLineMode();
    void setEndOfLineMode(EndOfLineMode eol);
    void setTextCodec(QByteArray encodeName, bool reload = false);

    BottomBar *bottomBar() { return m_bottomBar; }
    QString filePath() { return m_textEdit->filepath; }
    DTextEdit *textEditor() { return m_textEdit; }
    void hideWarningNotices();

    void checkForReload();
    void initToastPosition();

    void showNotify(const QString &message);

    //add by guoshaoyu
    BottomBar *m_bottomBar;
    bool getTextChangeFlag();
    void setTextChangeFlag(bool bFlag);

signals:
    void requestSaveAs();

private:
    void detectEndOfLine();
    void handleCursorModeChanged(DTextEdit::CursorMode mode);
    void handleHightlightChanged(const QString &name);
    void handleFileLoadFinished(const QByteArray &encode, const QString &content);
    void setTextCodec(QTextCodec *codec, bool reload = false);

protected:
    void resizeEvent(QResizeEvent *);

private:
    QHBoxLayout *m_layout;
    DTextEdit *m_textEdit;
    //modify guoshaoyu
    //BottomBar *m_bottomBar;
    QTextCodec *m_textCodec;

    EndOfLineMode m_endOfLineMode;
    bool m_isLoadFinished;
    QDateTime m_modified;

    bool m_isRefreshing;
    WarningNotices *m_waringNotices;
    bool m_bTextChange = true;

public slots:
    void slotTextChange();
};

#endif
