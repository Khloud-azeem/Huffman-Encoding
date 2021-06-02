#include "compressor2.h"
#include "readwrite.h"
#include "huffmantree.h"
#include "serialization.h"
#include "ui_compressor2.h"
#include<QFile>
#include<QFileDialog>
#include<QTextStream>
#include <QMessageBox>

compressor2::compressor2(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::compressor2)
{
    ui->setupUi(this);
}

compressor2::~compressor2()
{
    delete ui;
}


void compressor2::on_Browse_pic_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,tr("Open pgm"), "Desktop", tr("Image Files (*.pgm)"));
    ui->picture_path->setText(fileName);
}

void compressor2::on_Show_pic_clicked()
{
    QString pic_path= ui->picture_path->toPlainText();
        QPixmap pixmap(pic_path);
        ui->picture->setPixmap(pixmap) ;


}

void compressor2::on_compress_clicked()
{


    QString picture_path = ui->picture_path->toPlainText() ;

      int height = 0;

      int width = 0;
    std::string pict = picture_path. toStdString();
      vector<uint8_t> arr = readpgm(width, height, pict);
      CountFreq(arr, height * width);

      map<int, string> encTable = HuffmanCodes(freq);

      QString enc_enc_file = QFileDialog::getSaveFileName(this,tr("save enc"), "Desktop", tr("(*.enc )"));
       QFile f(enc_enc_file);
      f.flush();
      f.close();
      std::string enc_path = enc_enc_file. toStdString();


      QString frq = QFileDialog::getSaveFileName(this,tr("save enc"), "Desktop", tr("(*.frq )"));
      QFile m(frq);
      m.flush();
      m.close();
      std::string frq_file = frq. toStdString();

      serialize(encTable, arr, width, height, freq,enc_path,frq_file);

}



void compressor2::on_Browse_enc_clicked()
{
    QString enc_file = QFileDialog::getOpenFileName(this,tr("Open enc"), "Desktop", tr("(*.enc)"));
    ui->enc_path->setText(enc_file);

}

void compressor2::on_Browse_frq_clicked()
{
    QString frq_file = QFileDialog::getOpenFileName(this,tr("Open frq"), "Desktop", tr("(*.frq)"));
    ui->frq_path->setText(frq_file);

}

void compressor2::on_decompress_clicked()
{       vector <int>freq(256,0);
        QString enc_file =ui->enc_path->toPlainText() ;
        QString frq_file =ui->frq_path->toPlainText() ;
        std::string encfile = enc_file. toStdString();
        std::string frqfile = frq_file. toStdString();

         string bits=" ";
             int w=0;
             int h=0;
          deserialize (encfile, frqfile,freq, bits,w,h);


         map<int, string> encTable = HuffmanCodes(freq);
          map<string, int> invTable = InverseCode(encTable);
          vector<uint8_t> newimg = decode(bits, invTable, w, h);

          QString qstr = QFileDialog::getSaveFileName(this,tr("Open pgm"), "Desktop", tr("Image Files (*.pgm)"));
          QFile s(qstr);
          s.open( QIODevice::WriteOnly  );
          s.close();
          std::string writtenfile = qstr. toStdString();
          writepgm(newimg, w, h , writtenfile);

}


void compressor2::on_reset_clicked()
{
    ui->picture_path->clear();
        ui->enc_path->clear();
        ui->frq_path->clear();
        ui->comp_ratio->clear();
        ui->picture->clear();

}
