#ifndef VEXPLORER_H
#define VEXPLORER_H

#include <QWidget>

#include "vnavigationmode.h"

class QPushButton;
class VTreeWidget;
class QTreeWidgetItem;
class QShowEvent;
class QFocusEvent;
class QComboBox;
class VLineEdit;

class VExplorer : public QWidget, public VNavigationMode
{
    Q_OBJECT
public:
    explicit VExplorer(QWidget *p_parent = nullptr);

    // Implementations for VNavigationMode.
    void showNavigation() Q_DECL_OVERRIDE;
    bool handleKeyNavigation(int p_key, bool &p_succeed) Q_DECL_OVERRIDE;

protected:
    void showEvent(QShowEvent *p_event) Q_DECL_OVERRIDE;

    void focusInEvent(QFocusEvent *p_event) Q_DECL_OVERRIDE;

private:
    void setupUI();

    void init();

    void updateUI();

    bool m_initialized;

    bool m_uiInitialized;

    QPushButton *m_openBtn;
    QPushButton *m_openLocationBtn;
    QPushButton *m_starBtn;
    QComboBox *m_dirCB;
    VLineEdit *m_imgFolderEdit;
    VTreeWidget *m_tree;
};

#endif // VEXPLORER_H
