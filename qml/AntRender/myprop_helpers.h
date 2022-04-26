#pragma once

#include <QObject>
#include <QQmlEngine>

#define MYSIMPLE_PROP(pType, pName) \
    Q_PROPERTY(pType pName READ pName WRITE pName NOTIFY pName##Changed) \
    public: void pName(const pType& pVal) { if( pName##_ != pVal ) { pName##_ = pVal; Q_EMIT pName##Changed(pVal);} } \
    public: pType pName() const { return pName##_; } \
    private: pType pName##_{}; \
    Q_SIGNAL void pName##Changed(const pType& pVal); \
    private:
