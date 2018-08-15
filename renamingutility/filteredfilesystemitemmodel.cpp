#include "./filteredfilesystemitemmodel.h"

namespace RenamingUtility {

/*
    TRANSLATOR RenamingUtility::FilteredFileSystemItemModel
    Necessary for lupdate.
*/

FilteredFileSystemItemModel::FilteredFileSystemItemModel(ItemStatus statusFilter, QObject *parent)
    : QSortFilterProxyModel(parent)
    , m_statusFilter(statusFilter)
{
}

bool FilteredFileSystemItemModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    const auto sourceIndex = sourceModel()->index(sourceRow, 0, sourceParent);
    if (!sourceIndex.isValid()) {
        return false;
    }
    const auto *const item = reinterpret_cast<FileSystemItem *>(sourceIndex.internalPointer());
    if (!item) {
        return false;
    }

    if (item->status() == m_statusFilter || (item->status() == ItemStatus::Current && !item->counterpart() && !item->note().isEmpty())) {
        return true;
    }
    if (item->type() != ItemType::Dir) {
        return false;
    }

    auto child = sourceIndex.child(0, 0);
    while (child.isValid()) {
        if (filterAcceptsRow(child.row(), sourceIndex)) {
            return true;
        }
        child = sourceIndex.child(child.row() + 1, 0);
    }
    return false;
}

bool FilteredFileSystemItemModel::filterAcceptsColumn(int sourceColumn, const QModelIndex &) const
{
    switch (m_statusFilter) {
    case ItemStatus::Current:
        return sourceColumn == 0;
    case ItemStatus::New:
        return sourceColumn == 1 || sourceColumn == 2;
    }
    return false;
}

} // namespace RenamingUtility
