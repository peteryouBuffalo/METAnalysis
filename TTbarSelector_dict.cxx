// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME TTbarSelector_dict

/*******************************************************************/
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define G__DICTIONARY
#include "RConfig.h"
#include "TClass.h"
#include "TDictAttributeMap.h"
#include "TInterpreter.h"
#include "TROOT.h"
#include "TBuffer.h"
#include "TMemberInspector.h"
#include "TInterpreter.h"
#include "TVirtualMutex.h"
#include "TError.h"

#ifndef G__ROOT
#define G__ROOT
#endif

#include "RtypesImp.h"
#include "TIsAProxy.h"
#include "TFileMergeInfo.h"
#include <algorithm>
#include "TCollectionProxyInfo.h"
/*******************************************************************/

#include "TDataMember.h"

// Since CINT ignores the std namespace, we need to do so in this file.
namespace std {} using namespace std;

// Header files passed as explicit arguments
#include "TTbarSelector.h"

// Header files passed via #pragma extra_include

namespace ROOT {
   static void *new_TTbarSelector(void *p = 0);
   static void *newArray_TTbarSelector(Long_t size, void *p);
   static void delete_TTbarSelector(void *p);
   static void deleteArray_TTbarSelector(void *p);
   static void destruct_TTbarSelector(void *p);
   static void streamer_TTbarSelector(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TTbarSelector*)
   {
      ::TTbarSelector *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TTbarSelector >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TTbarSelector", ::TTbarSelector::Class_Version(), "TTbarSelector.h", 27,
                  typeid(::TTbarSelector), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::TTbarSelector::Dictionary, isa_proxy, 16,
                  sizeof(::TTbarSelector) );
      instance.SetNew(&new_TTbarSelector);
      instance.SetNewArray(&newArray_TTbarSelector);
      instance.SetDelete(&delete_TTbarSelector);
      instance.SetDeleteArray(&deleteArray_TTbarSelector);
      instance.SetDestructor(&destruct_TTbarSelector);
      instance.SetStreamerFunc(&streamer_TTbarSelector);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TTbarSelector*)
   {
      return GenerateInitInstanceLocal((::TTbarSelector*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::TTbarSelector*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr TTbarSelector::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *TTbarSelector::Class_Name()
{
   return "TTbarSelector";
}

//______________________________________________________________________________
const char *TTbarSelector::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TTbarSelector*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int TTbarSelector::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TTbarSelector*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TTbarSelector::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TTbarSelector*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TTbarSelector::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TTbarSelector*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void TTbarSelector::Streamer(TBuffer &R__b)
{
   // Stream an object of class TTbarSelector.

   TSelector::Streamer(R__b);
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_TTbarSelector(void *p) {
      return  p ? new(p) ::TTbarSelector : new ::TTbarSelector;
   }
   static void *newArray_TTbarSelector(Long_t nElements, void *p) {
      return p ? new(p) ::TTbarSelector[nElements] : new ::TTbarSelector[nElements];
   }
   // Wrapper around operator delete
   static void delete_TTbarSelector(void *p) {
      delete ((::TTbarSelector*)p);
   }
   static void deleteArray_TTbarSelector(void *p) {
      delete [] ((::TTbarSelector*)p);
   }
   static void destruct_TTbarSelector(void *p) {
      typedef ::TTbarSelector current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_TTbarSelector(TBuffer &buf, void *obj) {
      ((::TTbarSelector*)obj)->::TTbarSelector::Streamer(buf);
   }
} // end of namespace ROOT for class ::TTbarSelector

namespace {
  void TriggerDictionaryInitialization_TTbarSelector_dict_Impl() {
    static const char* headers[] = {
"TTbarSelector.h",
0
    };
    static const char* includePaths[] = {
"/cvmfs/cms.cern.ch/slc7_amd64_gcc820/lcg/root/6.14.09/include",
"/uscms/homes/p/peteryou/CMSSW_10_6_4/src/METAnalysis/",
0
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "TTbarSelector_dict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class __attribute__((annotate("$clingAutoload$TTbarSelector.h")))  TTbarSelector;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "TTbarSelector_dict dictionary payload"

#ifndef G__VECTOR_HAS_CLASS_ITERATOR
  #define G__VECTOR_HAS_CLASS_ITERATOR 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
#include "TTbarSelector.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"TTbarSelector", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("TTbarSelector_dict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_TTbarSelector_dict_Impl, {}, classesHeaders, /*has no C++ module*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_TTbarSelector_dict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_TTbarSelector_dict() {
  TriggerDictionaryInitialization_TTbarSelector_dict_Impl();
}
