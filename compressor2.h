#ifndef COMPRESSOR2_H
#define COMPRESSOR2_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class compressor2; }
QT_END_NAMESPACE

class compressor2 : public QMainWindow
{
    Q_OBJECT

public:
    compressor2(QWidget *parent = nullptr);
    ~compressor2();

private slots:
    void on_Browse_pic_clicked();

    void on_Show_pic_clicked();

    void on_compress_clicked();

    void on_Browse_enc_clicked();

    void on_Browse_frq_clicked();

    void on_reset_clicked();

    void on_decompress_clicked();

private:
    Ui::compressor2 *ui;
};
#endif // COMPRESSOR2_H
