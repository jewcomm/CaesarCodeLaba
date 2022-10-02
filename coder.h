#ifndef CODER_H
#define CODER_H

#include <QObject>

class Coder : public QObject
{
    Q_OBJECT
public:
    Coder(QObject *parent = nullptr);

public slots:
    void changemodeAlphabet(int mmodeAlphabet);
    void changeModeCode(bool mode);
    void setShift(int mShift);
    void setCoding(QString mUncoded);
    void setDecoding(QString mCoded);
    void alphabetWithShift();
    void updateCodeDecode();
    void coding();
    void decoding();

signals:
    void getAlphabet(QString alphabet);
    void getMutAlphabet(QString mutAlphabet);
    void getCoderedText(QString text);
    void getDecoderedText(QString text);

private:
    QTextCodec* codecFromUTFtoCP;

    int modeAlphabet = 1;
    int shift = 1;

    // 0 - coding
    // 1 - decoding
    bool modeCoding = 0;


    QString uncoded;
    QString coded;

    QByteArray full;        // modeAlphabet - 1
    QByteArray withoutEI;   // modeAlphabet - 2
    QByteArray withoutI;    // modeAlphabet - 3
    QByteArray withoutE;    // modeAlphabet - 4

    int foundIn(unsigned char symb, QByteArray source);
};

#endif // CODER_H
