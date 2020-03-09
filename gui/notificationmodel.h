#ifndef NOTIFICATIONMODEL_H
#define NOTIFICATIONMODEL_H

#include <tagparser/diagnostics.h>

#include <QAbstractListModel>

namespace QtGui {

class DiagModel : public QAbstractListModel {
    Q_OBJECT
public:
    explicit DiagModel(QObject *parent = nullptr);

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    int columnCount(const QModelIndex &parent) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    const TagParser::Diagnostics &diagnostics() const;
    void setDiagnostics(const TagParser::Diagnostics &diagnostics);

    static const QIcon &informationIcon();
    static const QIcon &warningIcon();
    static const QIcon &errorIcon();
    static const QIcon &debugIcon();

Q_SIGNALS:

public Q_SLOTS:

private:
    TagParser::Diagnostics m_diag;
};

} // namespace QtGui

#endif // NOTIFICATIONMODEL_H
