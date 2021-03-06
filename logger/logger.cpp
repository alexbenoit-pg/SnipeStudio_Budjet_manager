#include "logger.h"

// probably i should log file into data path
logger::logger()
{
    data=new dataManager();
    log.setFileName(QDir::toNativeSeparators("./ssbm.log"));
    log.open(QIODevice::Append);
    timeFormat = "hh:mm:ss.zzz";
    delete data;
}

void logger::close()
{
    log.close();
}


void logger::infoM(QString infoMessage)
{
    data=new dataManager();
    if(data->getLoglevel()>0)
    {
        QTextStream fout(&log);
        fout<<QTime::currentTime().toString(timeFormat)<<",I,"<<infoMessage+"\n";
    }
    delete data;
}


void logger::debugM(QString debugMessage)
{
    data=new dataManager();
    if(data->getLoglevel()>1)
    {
        QTextStream fout(&log);
        fout<<QTime::currentTime().toString(timeFormat)<<",D,"<<debugMessage+"\n";
    }
    delete data;
}

void logger::errorM(QString errorMessage)
{
    data=new dataManager();
    if(data->getLoglevel()>0)
    {
        QTextStream fout(&log);
        fout<<QTime::currentTime().toString(timeFormat)<<",E,"<<errorMessage+"\n";
    }
    delete data;
}

void logger::warningM(QString warningMessage)
{
    data=new dataManager();
    if(data->getLoglevel()>1)
    {
        QTextStream fout(&log);
        fout<<QTime::currentTime().toString(timeFormat)<<",W,"<<warningMessage+"\n";
    }
    delete data;
}
