#include "coder.h"
#include "QtDebug"
#include "QTextCodec"

Coder::Coder(QObject *parent) : QObject(parent)
{
    codecFromUTFtoCP = QTextCodec::codecForName("CP1251");
    full = codecFromUTFtoCP->fromUnicode("абвгдеёжзийклмнопрстуфхцчшщъыьэюя");
    withoutE = codecFromUTFtoCP->fromUnicode("абвгдежзийклмнопрстуфхцчшщъыьэюя");
    withoutI = codecFromUTFtoCP->fromUnicode("абвгдеёжзиклмнопрстуфхцчшщъыьэюя");
    withoutEI = codecFromUTFtoCP->fromUnicode("абвгдежзиклмнопрстуфхцчшщъыьэюя");
}

void Coder::changemodeAlphabet(int mmodeAlphabet){
    modeAlphabet = mmodeAlphabet;
    switch (modeAlphabet) {
    case 1:
        emit getAlphabet(codecFromUTFtoCP->toUnicode(full));
        break;
    case 2:
        emit getAlphabet(codecFromUTFtoCP->toUnicode(withoutEI));
        break;
    case 3:
        emit getAlphabet(codecFromUTFtoCP->toUnicode(withoutI));
        break;
    case 4:
        emit getAlphabet(codecFromUTFtoCP->toUnicode(withoutE));
        break;
    }
    updateCodeDecode();
    alphabetWithShift();
}

void Coder::changeModeCode(bool mode){
    modeCoding = mode;
}

void Coder::setShift(int mShift){
    shift = mShift;
    updateCodeDecode();
    alphabetWithShift();
}

void Coder::alphabetWithShift(){
    QByteArray temp;
    QByteArray *source;
    switch (modeAlphabet) {
    case 1:
        source = &full;
        break;

    case 2:
        source = &withoutEI;
        break;

    case 3:
        source = &withoutI;
        break;

    case 4:
        source = &withoutE;
        break;

    default:
        source = &full;
        break;
    }

    for(int i = 0; i < source->size(); i++){
        temp.append( (unsigned char)(( (unsigned char)(*source)[(i + shift) % source->size()] )));
    }

    emit getMutAlphabet(codecFromUTFtoCP->toUnicode(temp));
}

void Coder::updateCodeDecode(){
    if(modeCoding) coding();
    else decoding();
}

void Coder::setCoding(QString mUncoded){
    uncoded = mUncoded;
    coding();
    alphabetWithShift();
}

void Coder::setDecoding(QString mCoded){
    coded = mCoded;
    decoding();
    alphabetWithShift();
}

void Coder::coding() {
    QByteArray raw = codecFromUTFtoCP->fromUnicode(uncoded);
    QByteArray *source;
    QByteArray retval;
    switch (modeAlphabet) {
    case 1:
        source = &full;
        break;

    case 2:
        source = &withoutEI;
        break;

    case 3:
        source = &withoutI;
        break;

    case 4:
        source = &withoutE;
        break;

    default:
        source = &full;
        break;
    }
    for(int i = 0; i < raw.size(); i++){
        int index = foundIn(raw[i], *source);
        if(index == -1) retval.append(raw[i]);
        else {
            retval.append((unsigned char)(((unsigned char)(*source)[(index + shift) % source->size()])));
        }
    }
    emit getCoderedText(codecFromUTFtoCP->toUnicode(retval));
}

void Coder::decoding(){
    QByteArray raw = codecFromUTFtoCP->fromUnicode(coded);
    QByteArray *source;
    QByteArray retval;
    switch (modeAlphabet) {
    case 1:
        source = &full;
        break;

    case 2:
        source = &withoutEI;
        break;

    case 3:
        source = &withoutI;
        break;

    case 4:
        source = &withoutE;
        break;

    default:
        source = &full;
        break;
    }
    for(int i = 0; i < raw.size(); i++){
        int index = foundIn(raw[i], *source);
        if(index == -1) retval.append(raw[i]);
        else {
            retval.append((unsigned char)(((unsigned char)(*source)[(index + (source->size() - shift)) % source->size()])));
        }
    }
    emit getDecoderedText(codecFromUTFtoCP->toUnicode(retval));
}

int Coder::foundIn(unsigned char symb, QByteArray source){
    for(int i = 0; i < source.size(); i++){
        if((unsigned char)source[i] == symb) return i;
    }
    return -1;
}
