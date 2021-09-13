#include "dataextractor.h"

dataExtractor::dataExtractor():QObject(nullptr)
{

}

qint64 dataExtractor::dataUnpack()
{

    return dataStream;
}
