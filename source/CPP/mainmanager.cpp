#include "mainmanager.h"

QStringList MainManager::getAllExecutables()
{
	QStringList list = m_qml->getAllSoFiles();
	list << m_plg->getAllSoFiles();
	list << m_executablepath;

	return list;
}

MainManager::MainManager(CppManager *cpp, QmlManager *qml, OutputManager *out,
                         PluginManager *plg, BuildManager* bld, QObject *parent)
	: BaseClass(parent)
{
	setState(0);

	m_cpp = cpp;
	m_qml = qml;
	m_out = out;
	m_plg = plg;
    m_bld = bld;

    connect(m_bld, &BuildManager::finished, this, &MainManager::buildFinished);

}

void MainManager::buildFinished(){
    emit outDirChanged();
    m_qml->start();
    m_plg->start();
    m_cpp->start(getAllExecutables());
}

void MainManager::prepare(const QString &qtdir, const QString &projectdir)
{
	QStringList list;
    list << qtdir  << projectdir ;

	for (QString &S : list)
        if (S[S.count() - 1] == '/') S.remove(S.count() - 1, 1);

	m_qtdir = list[0];
    m_projectdir = list[1];

    m_bld->build();
}

void MainManager::start(bool erase)
{
	setState(1);

	m_out->copyAll(m_cpp->getQtLibrariesFullPaths(), m_cpp->cppLibraries(),
				   m_qml->foundImports(), m_plg->neededPlugins(), erase);

	setState(2);
}

bool MainManager::hasPrems(const QString &path)
{
	QFileInfo info(path);
	return (info.isReadable() && info.isWritable());
}

QString MainManager::stringFromUrl(QString url)
{
	return url.remove("file://");
}

bool MainManager::pathExists(bool isdir, const QString &path)
{
	if (isdir) return QDir(path).exists();
	return QFile(path).exists();
}

const QString& MainManager::outDir() const{
    return m_outputdir;
}

void MainManager::setState(int state)
{
	if (m_state == state) return;

	m_state = state;
	emit stateChanged(m_state);
}

int MainManager::state() const { return m_state; }
