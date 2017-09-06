#include "ui_formmain.h"
#include <QString>
#include <QFile>
#include <QTextStream>

int main( int argc, char ** argv )
{
    QApplication app( argc, argv );
    Ui_formMain w;
    if(argc>1)
    {
        QString param(argv[1]);

        if(param.contains(".ISO") || param.contains(".iso"))
        {
            param=param.replace("\\","/");
            w.leSrc->setText(param);
            if(param.contains(".ISO"))
            {
                QString fichierDest=param.section(".ISO",0,0);
                fichierDest+=".cso";
                w.leDest->setText(fichierDest);
            }
            if(param.contains(".iso"))
            {
                QString fichierDest=param.section(".iso",0,0);
                fichierDest+=".cso";
                w.leDest->setText(fichierDest);
            }
        }
        if(param.contains(".CSO") || param.contains(".cso"))
        {
            w.panneaux->setCurrentIndex(w.panneaux->indexOf(w.TabPage));
            w.leSrcDecomp->setText(param);
        }
        if(param.contains(".DAX") || param.contains(".dax"))
        {
            w.panneaux->setCurrentIndex(w.panneaux->indexOf(w.TabPage));
            w.leSrcDecomp->setText(param);
        }
    }
    //Chargement du fichier option
    QFile OptionFile("option.txt");
    if( OptionFile.open(QIODevice::ReadOnly))
    {
        QTextStream fluxLecture (&OptionFile);
        QString chaineALire;
        QString convert;
        chaineALire=fluxLecture.readLine();
        if(chaineALire=="0.33 BETA" || chaineALire=="0.34 BETA" || chaineALire=="0.40 BETA")
        {
            chaineALire=fluxLecture.readLine();
            w.dirOpenSave=chaineALire;
            chaineALire=fluxLecture.readLine();
            int itemDrivePSPLetter = chaineALire.toInt();
            w.leSaveFolder->setText(w.dirOpenSave);
            w.bDriveLetter->setCurrentIndex(itemDrivePSPLetter);
            w.bDriveLetter_2->setCurrentIndex(itemDrivePSPLetter);
            chaineALire=fluxLecture.readLine();
            int itemStyle = chaineALire.toInt();
            w.cbStyle->setCurrentIndex(itemStyle);
            app.setStyle(w.cbStyle->currentText());
            w.cbCompressType="FILE";
        }
    }
    else
    {
        w.bDriveLetter->setCurrentIndex(0);
        w.dirOpenSave="";
    }
    //w.show();

    app.connect( &app, SIGNAL( lastWindowClosed() ), &app, SLOT( quit() ) );

    return app.exec();
}
