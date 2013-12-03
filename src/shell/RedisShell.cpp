#include "shell/RedisShell.h"

#include <QKeyEvent>
#include <QStringListModel>
#include <QMenu>

#include "common/macros.h"
#include "gui/GuiFactory.h"
#include "shell/RedisLexer.h"

namespace fastoredis
{
    RedisShell::RedisShell(QWidget *parent)
        : base_class(parent)
    {
        setLexer(new RedisLexer(this));
        setAutoCompletionThreshold(1);
        setAutoCompletionSource(QsciScintilla::AcsAPIs);
        setAutoCompletionCaseSensitivity(false);

        VERIFY(connect(this, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(showContextMenu(const QPoint &))));
    }

    void RedisShell::showContextMenu(const QPoint &pt)
    {
        QMenu *menu = createStandardContextMenu();
        menu->exec(mapToGlobal(pt));
        delete menu;
    }

    void RedisShell::keyPressEvent(QKeyEvent *keyEvent)
    {
        if((keyEvent->modifiers() & Qt::ControlModifier) && (keyEvent->key() == Qt::Key_Return) ){
            emit executed();
        }
        return base_class::keyPressEvent(keyEvent);
    }
}

