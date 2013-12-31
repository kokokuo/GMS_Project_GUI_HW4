#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(800,600);
    view = new DrawView(&gmsModel); //取得GMSModel
    this->setCentralWidget(&scrollArea);
    scrollArea.setWidget(view);
    //透過此行讓放在ScrollArea中的Widget可以與scrollArea一起縮放,不過便不會有Scrollbar的出現
    //scrollArea.setWidgetResizable(true);
    scrollArea.horizontalScrollBar()->setValue(100);
    scrollArea.verticalScrollBar()->setValue(100);


    //Register synchronous event(SINGAL & SLOT) to close MainWindow
    //by menubar
    QObject::connect(ui->actionExitByMenuBar,SIGNAL(triggered()),this,SLOT(close()));
    //by toolbutton
    QObject::connect(ui->actionExitByToolBar,SIGNAL(triggered()),this,SLOT(close()));

    //open FileDialog
    QObject::connect(ui->actionOpenByMenuBar,SIGNAL(triggered()),this,SLOT(OnOpenFileButtonClicked()));
    QObject::connect(ui->actionOpenFolderByToolBar,SIGNAL(triggered()),this,SLOT(OnOpenFileButtonClicked()));


    view->update();
}

MainWindow::~MainWindow()
{
    delete ui;
}
//SLOT : When Click OpenFolder Action Control,it will have a slot OnOpenFileButtonClicked() and go here.
void MainWindow::OnOpenFileButtonClicked(){
    QString PathDestination = "graphical_Modeling_system_GUI/GMS XML Files";
    QDir fileDir(QDir::currentPath());
    fileDir.cd("../" + PathDestination);
    fileName = QFileDialog::getOpenFileName(this,tr("Open GMS XML File"),
                                            fileDir.path(),tr("XML Files (*.xml)"));
    //載入檔案
    int code = gmsModel.LoadXMLFormatRecord(fileName.toLocal8Bit().constData());
    //測試輸出
    if(code == XMLErrorCode::OK){

        vector<Component*> components = this->gmsModel.GetComponents().GetAllComponent();
        cout << "Components:" << endl;
        cout << "------------------------------------------------------" <<endl;
        cout << "   Type   |   ID    |    Name    " <<endl;
        cout << "------------------------------------------------------" <<endl;
        for(vector<Component*>::iterator it = components.begin();it != components.end();it++){
            //使用C語言印出,為了能夠讓印出的格式排版整齊,[0]是擷取自串的字首
            printf("    %c     |   %2d    |    %s\n",(*it)->GetType()[0],(*it)->GetID(),(*it)->GetName().c_str());
        }
    }
    if(this->gmsModel.GetGroups().GetAllGroups().size() >0){

        map<string,Group*> groups = this->gmsModel.GetGroups().GetAllGroups();
        cout << "Groups:" << endl;
        cout << "------------------------------------------------------" <<endl;
        cout << "   GID   |   Name    |    Member    " <<endl;
        cout << "------------------------------------------------------" <<endl;
        for(map<string,Group*>::iterator it = groups.begin();it != groups.end();it++){
            printf("    %s     |   %s    |    %s\n",it->first.c_str(),(it->second)->GetName().c_str(),(it->second)->GetMembersIdByStringFormat().c_str());
        }
    }
    //設定出示繪圖座標
    view->SetComponentsDrawPostion();
    view->SetGroupsDrawPostion();
    //更新畫面
    view->update();
}


