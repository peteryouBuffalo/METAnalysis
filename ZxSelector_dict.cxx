// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME ZxSelector_dict

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
#include "src/ZxSelector.h"

// Header files passed via #pragma extra_include

namespace ROOT {
   static void *new_ZxSelector(void *p = 0);
   static void *newArray_ZxSelector(Long_t size, void *p);
   static void delete_ZxSelector(void *p);
   static void deleteArray_ZxSelector(void *p);
   static void destruct_ZxSelector(void *p);
   static void streamer_ZxSelector(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::ZxSelector*)
   {
      ::ZxSelector *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::ZxSelector >(0);
      static ::ROOT::TGenericClassInfo 
         instance("ZxSelector", ::ZxSelector::Class_Version(), "src/ZxSelector.h", 22,
                  typeid(::ZxSelector), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::ZxSelector::Dictionary, isa_proxy, 16,
                  sizeof(::ZxSelector) );
      instance.SetNew(&new_ZxSelector);
      instance.SetNewArray(&newArray_ZxSelector);
      instance.SetDelete(&delete_ZxSelector);
      instance.SetDeleteArray(&deleteArray_ZxSelector);
      instance.SetDestructor(&destruct_ZxSelector);
      instance.SetStreamerFunc(&streamer_ZxSelector);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::ZxSelector*)
   {
      return GenerateInitInstanceLocal((::ZxSelector*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::ZxSelector*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr ZxSelector::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *ZxSelector::Class_Name()
{
   return "ZxSelector";
}

//______________________________________________________________________________
const char *ZxSelector::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::ZxSelector*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int ZxSelector::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::ZxSelector*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *ZxSelector::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::ZxSelector*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *ZxSelector::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::ZxSelector*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void ZxSelector::Streamer(TBuffer &R__b)
{
   // Stream an object of class ZxSelector.

   TSelector::Streamer(R__b);
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_ZxSelector(void *p) {
      return  p ? new(p) ::ZxSelector : new ::ZxSelector;
   }
   static void *newArray_ZxSelector(Long_t nElements, void *p) {
      return p ? new(p) ::ZxSelector[nElements] : new ::ZxSelector[nElements];
   }
   // Wrapper around operator delete
   static void delete_ZxSelector(void *p) {
      delete ((::ZxSelector*)p);
   }
   static void deleteArray_ZxSelector(void *p) {
      delete [] ((::ZxSelector*)p);
   }
   static void destruct_ZxSelector(void *p) {
      typedef ::ZxSelector current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_ZxSelector(TBuffer &buf, void *obj) {
      ((::ZxSelector*)obj)->::ZxSelector::Streamer(buf);
   }
} // end of namespace ROOT for class ::ZxSelector

namespace {
  void TriggerDictionaryInitialization_ZxSelector_dict_Impl() {
    static const char* headers[] = {
"src/ZxSelector.h",
0
    };
    static const char* includePaths[] = {
"/cvmfs/cms.cern.ch/slc7_amd64_gcc820/lcg/root/6.14.09/include",
"/uscms/homes/p/peteryou/CMSSW_10_6_4/src/METAnalysis/",
0
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "ZxSelector_dict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class __attribute__((annotate("$clingAutoload$src/ZxSelector.h")))  ZxSelector;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "ZxSelector_dict dictionary payload"

#ifndef G__VECTOR_HAS_CLASS_ITERATOR
  #define G__VECTOR_HAS_CLASS_ITERATOR 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
#include "src/ZxSelector.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"ZxSelector", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("ZxSelector_dict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_ZxSelector_dict_Impl, {}, classesHeaders, /*has no C++ module*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_ZxSelector_dict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_ZxSelector_dict() {
  TriggerDictionaryInitialization_ZxSelector_dict_Impl();
}
