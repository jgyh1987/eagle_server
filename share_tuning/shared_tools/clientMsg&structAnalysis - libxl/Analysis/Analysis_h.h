

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.01.0622 */
/* at Tue Jan 19 11:14:07 2038
 */
/* Compiler settings for Analysis.idl:
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


#ifndef __Analysis_h_h__
#define __Analysis_h_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IAnalysis_FWD_DEFINED__
#define __IAnalysis_FWD_DEFINED__
typedef interface IAnalysis IAnalysis;

#endif 	/* __IAnalysis_FWD_DEFINED__ */


#ifndef __Analysis_FWD_DEFINED__
#define __Analysis_FWD_DEFINED__

#ifdef __cplusplus
typedef class Analysis Analysis;
#else
typedef struct Analysis Analysis;
#endif /* __cplusplus */

#endif 	/* __Analysis_FWD_DEFINED__ */


#ifdef __cplusplus
extern "C"{
#endif 



#ifndef __Analysis_LIBRARY_DEFINED__
#define __Analysis_LIBRARY_DEFINED__

/* library Analysis */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_Analysis;

#ifndef __IAnalysis_DISPINTERFACE_DEFINED__
#define __IAnalysis_DISPINTERFACE_DEFINED__

/* dispinterface IAnalysis */
/* [uuid] */ 


EXTERN_C const IID DIID_IAnalysis;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("273DFD09-CC31-4768-8DD6-E61A48FA9916")
    IAnalysis : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IAnalysisVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAnalysis * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAnalysis * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAnalysis * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IAnalysis * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IAnalysis * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IAnalysis * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IAnalysis * This,
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
    } IAnalysisVtbl;

    interface IAnalysis
    {
        CONST_VTBL struct IAnalysisVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAnalysis_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IAnalysis_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IAnalysis_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IAnalysis_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IAnalysis_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IAnalysis_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IAnalysis_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IAnalysis_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_Analysis;

#ifdef __cplusplus

class DECLSPEC_UUID("6219EA9B-E899-4A4A-9F89-C70C6FCBDCBB")
Analysis;
#endif
#endif /* __Analysis_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


