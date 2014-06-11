#ifndef DEBUGMANAGER_H
#define DEBUGMANAGER_H


#include <string>
#include <vector>

#include <QObject>
#include <QColor>
#include <QList>
#include <QRegExp>

#include "traceentry.h"

class QRegExp;

namespace Templar {

class TemplateEventHandler;
class UsedSourceFileModel;

class DebugManager : public QObject
{
public:
    DebugManager(QObject *parent = 0);

    void addEventHandler(TemplateEventHandler* handler);
    int getEventCount() const;

    void inspect(const TraceEntry& entry);
    void selectRoot(const TraceEntry& entry);

    void setBreakpoints(const QList<QRegExp>& breakpoints) {
        this->breakpoints = breakpoints;
    }
    TraceEntry &getEntryTarget() { return traceEntryTarget; }
    void gotoFile(size_t fileId);
    void setUsedFileModel(UsedSourceFileModel *usedSourceFiles);
public slots:
    void next();
    void prev();
    void forward();
    void rewind();
    void reset();

private:
    bool hasBreakpoint(const QString& str) const;

private:

    QList<TemplateEventHandler*> eventHandlers;
    std::vector<const TraceEntry *> navigationHistory;
    std::vector<const TraceEntry *> rootHistory;

    UsedSourceFileModel *usedFiles;
    TraceEntry traceEntryTarget;
    unsigned int historyPos;

    QList<QRegExp> breakpoints;
};

} // namespace Templar

#endif // DEBUGMANAGER_H
