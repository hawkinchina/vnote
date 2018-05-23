#include "vexplorer.h"

#include <QtWidgets>

#include "utils/viconutils.h"
#include "utils/vutils.h"
#include "vconfigmanager.h"
#include "vmainwindow.h"
#include "vcart.h"
#include "vlineedit.h"
#include "vtreewidget.h"

extern VMainWindow *g_mainWin;

extern VConfigManager *g_config;

VExplorer::VExplorer(QWidget *p_parent)
    : QWidget(p_parent),
      m_initialized(false),
      m_uiInitialized(false)
{
}

void VExplorer::setupUI()
{
    if (m_uiInitialized) {
        return;
    }

    m_uiInitialized = true;

    QLabel *dirLabel = new QLabel(tr("Directory"), this);

    m_openBtn = new QPushButton(VIconUtils::buttonIcon(":/resources/icons/dir_item.svg"), "", this);
    m_openBtn->setToolTip(tr("Open"));
    m_openBtn->setProperty("FlatBtn", true);

    m_openLocationBtn = new QPushButton(VIconUtils::buttonIcon(":/resources/icons/open_location.svg"), "", this);
    m_openLocationBtn->setToolTip(tr("Open Directory Location"));
    m_openLocationBtn->setProperty("FlatBtn", true);

    m_starBtn = new QPushButton(VIconUtils::buttonIcon(":/resources/icons/star.svg"), "", this);
    m_starBtn->setToolTip(tr("Star"));
    m_starBtn->setProperty("FlatBtn", true);

    QHBoxLayout *dirLayout = new QHBoxLayout();
    dirLayout->addWidget(dirLabel);
    dirLayout->addStretch();
    dirLayout->addWidget(m_openBtn);
    dirLayout->addWidget(m_openLocationBtn);
    dirLayout->addWidget(m_starBtn);
    dirLayout->setContentsMargins(0, 0, 0, 0);

    m_dirCB = VUtils::getComboBox(this);
    m_dirCB->setEditable(true);
    m_dirCB->setLineEdit(new VLineEdit(this));
    m_dirCB->setToolTip(tr("Path of the directory to explore"));
    m_dirCB->lineEdit()->setPlaceholderText(tr("Press Enter to confirm the path"));
    m_dirCB->lineEdit()->setProperty("EmbeddedEdit", true);
    m_dirCB->completer()->setCaseSensitivity(Qt::CaseSensitive);

    QLabel *imgLabel = new QLabel(tr("Image Folder"), this);

    m_imgFolderEdit = new VLineEdit(this);
    m_imgFolderEdit->setPlaceholderText(tr("Use global configuration (%1)")
                                          .arg(g_config->getImageFolderExt()));

    m_tree = new VTreeWidget(this);
    m_tree->setColumnCount(1);
    m_tree->setHeaderHidden(true);
    m_tree->setContextMenuPolicy(Qt::CustomContextMenu);

    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addLayout(dirLayout);
    mainLayout->addWidget(m_dirCB);
    mainLayout->addWidget(imgLabel);
    mainLayout->addWidget(m_imgFolderEdit);
    mainLayout->addWidget(m_tree);
    mainLayout->setContentsMargins(3, 0, 3, 0);

    setLayout(mainLayout);
}

void VExplorer::init()
{
    if (m_initialized) {
        return;
    }

    m_initialized = true;

    setupUI();
}

void VExplorer::showNavigation()
{
    setupUI();

    VNavigationMode::showNavigation(m_tree);
}

bool VExplorer::handleKeyNavigation(int p_key, bool &p_succeed)
{
    static bool secondKey = false;
    setupUI();

    return VNavigationMode::handleKeyNavigation(m_tree,
                                                secondKey,
                                                p_key,
                                                p_succeed);
}

void VExplorer::showEvent(QShowEvent *p_event)
{
    init();

    QWidget::showEvent(p_event);
}

void VExplorer::focusInEvent(QFocusEvent *p_event)
{
    init();

    QWidget::focusInEvent(p_event);
    m_tree->setFocus();
}

void VExplorer::updateUI()
{

}
