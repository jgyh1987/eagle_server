

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.01.0622 */
/* at Tue Jan 19 11:14:07 2038
 */
/* Compiler settings for ConfigAnalysis.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 8.01.0622 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */



/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 500
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif /* __RPCNDR_H_VERSION__ */


#ifndef __ConfigAnalysis_h_h__
#define __ConfigAnalysis_h_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IConfigAnalysis_FWD_DEFINED__
#define __IConfigAnalysis_FWD_DEFINED__
typedef interface IConfigAnalysis IConfigAnalysis;

#endif 	/* __IConfigAnalysis_FWD_DEFINED__ */


#ifndef __ConfigAnalysis_FWD_DEFINED__
#define __ConfigAnalysis_FWD_DEFINED__

#ifdef __cplusplus
typedef class ConfigAnalysis ConfigAnalysis;
#else
typedef struct ConfigAnalysis ConfigAnalysis;
#endif /* __cplusplus */

#endif 	/* __ConfigAnalysis_FWD_DEFINED__ */


#ifdef __cplusplus
extern "C"{
#endif 



#ifndef __ConfigAnalysis_LIBRARY_DEFINED__
#define __ConfigAnalysis_LIBRARY_DEFINED__

/* library ConfigAnalysis */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_ConfigAnalysis;

#ifndef __IConfigAnalysis_DISPINTERFACE_DEFINED__
#define __IConfigAnalysis_DISPINTERFACE_DEFINED__

/* dispinterface IConfigAnalysis */
/* [uuid] */ 


EXTERN_C const IID DIID_IConfigAnalysis;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("599B5B7F-0CD6-485C-B0F3-09F9C07BB47A")
    IConfigAnalysis : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IConfigAnalysisVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IConfigAnalysis * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IConfigAnalysis * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IConfigAnalysis * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IConfigAnalysis * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IConfigAnalysis * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IConfigAnalysis * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IConfigAnalysis * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        END_INTERFACE
    } IConfigAnalysisVtbl;

    interface IConfigAnalysis
    {
        CONST_VTBL struct IConfigAnalysisVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IConfigAnalysis_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IConfigAnalysis_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IConfigAnalysis_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IConfigAnalysis_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IConfigAnalysis_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IConfigAnalysis_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IConfigAnalysis_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IConfigAnalysis_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_ConfigAnalysis;

#ifdef __cplusplus

class DECLSPEC_UUID("F9E85656-F94A-4D9C-B0A6-7C9ABE833C87")
ConfigAnalysis;
#endif
#endif /* __ConfigAnalysis_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


