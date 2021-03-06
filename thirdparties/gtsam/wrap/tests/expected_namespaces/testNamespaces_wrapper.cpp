#include <wrap/matlab.h>
#include <map>

#include <path/to/ns1.h>
#include <path/to/ns1/ClassB.h>
#include <path/to/ns2.h>
#include <path/to/ns2/ClassA.h>
#include <path/to/ns3.h>


typedef std::set<boost::shared_ptr<ns1::ClassA>*> Collector_ns1ClassA;
static Collector_ns1ClassA collector_ns1ClassA;
typedef std::set<boost::shared_ptr<ns1::ClassB>*> Collector_ns1ClassB;
static Collector_ns1ClassB collector_ns1ClassB;
typedef std::set<boost::shared_ptr<ns2::ClassA>*> Collector_ns2ClassA;
static Collector_ns2ClassA collector_ns2ClassA;
typedef std::set<boost::shared_ptr<ns2::ns3::ClassB>*> Collector_ns2ns3ClassB;
static Collector_ns2ns3ClassB collector_ns2ns3ClassB;
typedef std::set<boost::shared_ptr<ns2::ClassC>*> Collector_ns2ClassC;
static Collector_ns2ClassC collector_ns2ClassC;
typedef std::set<boost::shared_ptr<ClassD>*> Collector_ClassD;
static Collector_ClassD collector_ClassD;

void _deleteAllObjects()
{
  mstream mout;
  std::streambuf *outbuf = std::cout.rdbuf(&mout);

  bool anyDeleted = false;
  { for(Collector_ns1ClassA::iterator iter = collector_ns1ClassA.begin();
      iter != collector_ns1ClassA.end(); ) {
    delete *iter;
    collector_ns1ClassA.erase(iter++);
    anyDeleted = true;
  } }
  { for(Collector_ns1ClassB::iterator iter = collector_ns1ClassB.begin();
      iter != collector_ns1ClassB.end(); ) {
    delete *iter;
    collector_ns1ClassB.erase(iter++);
    anyDeleted = true;
  } }
  { for(Collector_ns2ClassA::iterator iter = collector_ns2ClassA.begin();
      iter != collector_ns2ClassA.end(); ) {
    delete *iter;
    collector_ns2ClassA.erase(iter++);
    anyDeleted = true;
  } }
  { for(Collector_ns2ns3ClassB::iterator iter = collector_ns2ns3ClassB.begin();
      iter != collector_ns2ns3ClassB.end(); ) {
    delete *iter;
    collector_ns2ns3ClassB.erase(iter++);
    anyDeleted = true;
  } }
  { for(Collector_ns2ClassC::iterator iter = collector_ns2ClassC.begin();
      iter != collector_ns2ClassC.end(); ) {
    delete *iter;
    collector_ns2ClassC.erase(iter++);
    anyDeleted = true;
  } }
  { for(Collector_ClassD::iterator iter = collector_ClassD.begin();
      iter != collector_ClassD.end(); ) {
    delete *iter;
    collector_ClassD.erase(iter++);
    anyDeleted = true;
  } }
  if(anyDeleted)
    cout <<
      "WARNING:  Wrap modules with variables in the workspace have been reloaded due to\n"
      "calling destructors, call 'clear all' again if you plan to now recompile a wrap\n"
      "module, so that your recompiled module is used instead of the old one." << endl;
  std::cout.rdbuf(outbuf);
}

void _testNamespaces_RTTIRegister() {
  const mxArray *alreadyCreated = mexGetVariablePtr("global", "gtsam_testNamespaces_rttiRegistry_created");
  if(!alreadyCreated) {
    std::map<std::string, std::string> types;

    mxArray *registry = mexGetVariable("global", "gtsamwrap_rttiRegistry");
    if(!registry)
      registry = mxCreateStructMatrix(1, 1, 0, NULL);
    typedef std::pair<std::string, std::string> StringPair;
    for(const StringPair& rtti_matlab: types) {
      int fieldId = mxAddField(registry, rtti_matlab.first.c_str());
      if(fieldId < 0)
        mexErrMsgTxt("gtsam wrap:  Error indexing RTTI types, inheritance will not work correctly");
      mxArray *matlabName = mxCreateString(rtti_matlab.second.c_str());
      mxSetFieldByNumber(registry, 0, fieldId, matlabName);
    }
    if(mexPutVariable("global", "gtsamwrap_rttiRegistry", registry) != 0)
      mexErrMsgTxt("gtsam wrap:  Error indexing RTTI types, inheritance will not work correctly");
    mxDestroyArray(registry);
    
    mxArray *newAlreadyCreated = mxCreateNumericMatrix(0, 0, mxINT8_CLASS, mxREAL);
    if(mexPutVariable("global", "gtsam_testNamespaces_rttiRegistry_created", newAlreadyCreated) != 0)
      mexErrMsgTxt("gtsam wrap:  Error indexing RTTI types, inheritance will not work correctly");
    mxDestroyArray(newAlreadyCreated);
  }
}

void ns1ClassA_collectorInsertAndMakeBase_0(int nargout, mxArray *out[], int nargin, const mxArray *in[])
{
  mexAtExit(&_deleteAllObjects);
  typedef boost::shared_ptr<ns1::ClassA> Shared;

  Shared *self = *reinterpret_cast<Shared**> (mxGetData(in[0]));
  collector_ns1ClassA.insert(self);
}

void ns1ClassA_constructor_1(int nargout, mxArray *out[], int nargin, const mxArray *in[])
{
  mexAtExit(&_deleteAllObjects);
  typedef boost::shared_ptr<ns1::ClassA> Shared;

  Shared *self = new Shared(new ns1::ClassA());
  collector_ns1ClassA.insert(self);
  out[0] = mxCreateNumericMatrix(1, 1, mxUINT32OR64_CLASS, mxREAL);
  *reinterpret_cast<Shared**> (mxGetData(out[0])) = self;
}

void ns1ClassA_deconstructor_2(int nargout, mxArray *out[], int nargin, const mxArray *in[])
{
  typedef boost::shared_ptr<ns1::ClassA> Shared;
  checkArguments("delete_ns1ClassA",nargout,nargin,1);
  Shared *self = *reinterpret_cast<Shared**>(mxGetData(in[0]));
  Collector_ns1ClassA::iterator item;
  item = collector_ns1ClassA.find(self);
  if(item != collector_ns1ClassA.end()) {
    delete self;
    collector_ns1ClassA.erase(item);
  }
}

void ns1ClassB_collectorInsertAndMakeBase_3(int nargout, mxArray *out[], int nargin, const mxArray *in[])
{
  mexAtExit(&_deleteAllObjects);
  typedef boost::shared_ptr<ns1::ClassB> Shared;

  Shared *self = *reinterpret_cast<Shared**> (mxGetData(in[0]));
  collector_ns1ClassB.insert(self);
}

void ns1ClassB_constructor_4(int nargout, mxArray *out[], int nargin, const mxArray *in[])
{
  mexAtExit(&_deleteAllObjects);
  typedef boost::shared_ptr<ns1::ClassB> Shared;

  Shared *self = new Shared(new ns1::ClassB());
  collector_ns1ClassB.insert(self);
  out[0] = mxCreateNumericMatrix(1, 1, mxUINT32OR64_CLASS, mxREAL);
  *reinterpret_cast<Shared**> (mxGetData(out[0])) = self;
}

void ns1ClassB_deconstructor_5(int nargout, mxArray *out[], int nargin, const mxArray *in[])
{
  typedef boost::shared_ptr<ns1::ClassB> Shared;
  checkArguments("delete_ns1ClassB",nargout,nargin,1);
  Shared *self = *reinterpret_cast<Shared**>(mxGetData(in[0]));
  Collector_ns1ClassB::iterator item;
  item = collector_ns1ClassB.find(self);
  if(item != collector_ns1ClassB.end()) {
    delete self;
    collector_ns1ClassB.erase(item);
  }
}

void ns2ClassA_collectorInsertAndMakeBase_6(int nargout, mxArray *out[], int nargin, const mxArray *in[])
{
  mexAtExit(&_deleteAllObjects);
  typedef boost::shared_ptr<ns2::ClassA> Shared;

  Shared *self = *reinterpret_cast<Shared**> (mxGetData(in[0]));
  collector_ns2ClassA.insert(self);
}

void ns2ClassA_constructor_7(int nargout, mxArray *out[], int nargin, const mxArray *in[])
{
  mexAtExit(&_deleteAllObjects);
  typedef boost::shared_ptr<ns2::ClassA> Shared;

  Shared *self = new Shared(new ns2::ClassA());
  collector_ns2ClassA.insert(self);
  out[0] = mxCreateNumericMatrix(1, 1, mxUINT32OR64_CLASS, mxREAL);
  *reinterpret_cast<Shared**> (mxGetData(out[0])) = self;
}

void ns2ClassA_deconstructor_8(int nargout, mxArray *out[], int nargin, const mxArray *in[])
{
  typedef boost::shared_ptr<ns2::ClassA> Shared;
  checkArguments("delete_ns2ClassA",nargout,nargin,1);
  Shared *self = *reinterpret_cast<Shared**>(mxGetData(in[0]));
  Collector_ns2ClassA::iterator item;
  item = collector_ns2ClassA.find(self);
  if(item != collector_ns2ClassA.end()) {
    delete self;
    collector_ns2ClassA.erase(item);
  }
}

void ns2ClassA_memberFunction_9(int nargout, mxArray *out[], int nargin, const mxArray *in[])
{
  typedef boost::shared_ptr<ns2::ClassA> Shared;
  checkArguments("memberFunction",nargout,nargin-1,0);
  Shared obj = unwrap_shared_ptr<ns2::ClassA>(in[0], "ptr_ns2ClassA");
  out[0] = wrap< double >(obj->memberFunction());
}

void ns2ClassA_nsArg_10(int nargout, mxArray *out[], int nargin, const mxArray *in[])
{
  typedef boost::shared_ptr<ns2::ClassA> Shared;
  checkArguments("nsArg",nargout,nargin-1,1);
  Shared obj = unwrap_shared_ptr<ns2::ClassA>(in[0], "ptr_ns2ClassA");
  ns1::ClassB& arg = *unwrap_shared_ptr< ns1::ClassB >(in[1], "ptr_ns1ClassB");
  out[0] = wrap< int >(obj->nsArg(arg));
}

void ns2ClassA_nsReturn_11(int nargout, mxArray *out[], int nargin, const mxArray *in[])
{
  typedef boost::shared_ptr<ns2::ns3::ClassB> SharedClassB;
  typedef boost::shared_ptr<ns2::ClassA> Shared;
  checkArguments("nsReturn",nargout,nargin-1,1);
  Shared obj = unwrap_shared_ptr<ns2::ClassA>(in[0], "ptr_ns2ClassA");
  double q = unwrap< double >(in[1]);
  out[0] = wrap_shared_ptr(SharedClassB(new ns2::ns3::ClassB(obj->nsReturn(q))),"ns2.ns3.ClassB", false);
}

void ns2ClassA_afunction_12(int nargout, mxArray *out[], int nargin, const mxArray *in[])
{
  typedef boost::shared_ptr<ns2::ClassA> Shared;
  checkArguments("ns2ClassA.afunction",nargout,nargin,0);
  out[0] = wrap< double >(ns2::ClassA::afunction());
}

void ns2ns3ClassB_collectorInsertAndMakeBase_13(int nargout, mxArray *out[], int nargin, const mxArray *in[])
{
  mexAtExit(&_deleteAllObjects);
  typedef boost::shared_ptr<ns2::ns3::ClassB> Shared;

  Shared *self = *reinterpret_cast<Shared**> (mxGetData(in[0]));
  collector_ns2ns3ClassB.insert(self);
}

void ns2ns3ClassB_constructor_14(int nargout, mxArray *out[], int nargin, const mxArray *in[])
{
  mexAtExit(&_deleteAllObjects);
  typedef boost::shared_ptr<ns2::ns3::ClassB> Shared;

  Shared *self = new Shared(new ns2::ns3::ClassB());
  collector_ns2ns3ClassB.insert(self);
  out[0] = mxCreateNumericMatrix(1, 1, mxUINT32OR64_CLASS, mxREAL);
  *reinterpret_cast<Shared**> (mxGetData(out[0])) = self;
}

void ns2ns3ClassB_deconstructor_15(int nargout, mxArray *out[], int nargin, const mxArray *in[])
{
  typedef boost::shared_ptr<ns2::ns3::ClassB> Shared;
  checkArguments("delete_ns2ns3ClassB",nargout,nargin,1);
  Shared *self = *reinterpret_cast<Shared**>(mxGetData(in[0]));
  Collector_ns2ns3ClassB::iterator item;
  item = collector_ns2ns3ClassB.find(self);
  if(item != collector_ns2ns3ClassB.end()) {
    delete self;
    collector_ns2ns3ClassB.erase(item);
  }
}

void ns2ClassC_collectorInsertAndMakeBase_16(int nargout, mxArray *out[], int nargin, const mxArray *in[])
{
  mexAtExit(&_deleteAllObjects);
  typedef boost::shared_ptr<ns2::ClassC> Shared;

  Shared *self = *reinterpret_cast<Shared**> (mxGetData(in[0]));
  collector_ns2ClassC.insert(self);
}

void ns2ClassC_constructor_17(int nargout, mxArray *out[], int nargin, const mxArray *in[])
{
  mexAtExit(&_deleteAllObjects);
  typedef boost::shared_ptr<ns2::ClassC> Shared;

  Shared *self = new Shared(new ns2::ClassC());
  collector_ns2ClassC.insert(self);
  out[0] = mxCreateNumericMatrix(1, 1, mxUINT32OR64_CLASS, mxREAL);
  *reinterpret_cast<Shared**> (mxGetData(out[0])) = self;
}

void ns2ClassC_deconstructor_18(int nargout, mxArray *out[], int nargin, const mxArray *in[])
{
  typedef boost::shared_ptr<ns2::ClassC> Shared;
  checkArguments("delete_ns2ClassC",nargout,nargin,1);
  Shared *self = *reinterpret_cast<Shared**>(mxGetData(in[0]));
  Collector_ns2ClassC::iterator item;
  item = collector_ns2ClassC.find(self);
  if(item != collector_ns2ClassC.end()) {
    delete self;
    collector_ns2ClassC.erase(item);
  }
}

void ClassD_collectorInsertAndMakeBase_19(int nargout, mxArray *out[], int nargin, const mxArray *in[])
{
  mexAtExit(&_deleteAllObjects);
  typedef boost::shared_ptr<ClassD> Shared;

  Shared *self = *reinterpret_cast<Shared**> (mxGetData(in[0]));
  collector_ClassD.insert(self);
}

void ClassD_constructor_20(int nargout, mxArray *out[], int nargin, const mxArray *in[])
{
  mexAtExit(&_deleteAllObjects);
  typedef boost::shared_ptr<ClassD> Shared;

  Shared *self = new Shared(new ClassD());
  collector_ClassD.insert(self);
  out[0] = mxCreateNumericMatrix(1, 1, mxUINT32OR64_CLASS, mxREAL);
  *reinterpret_cast<Shared**> (mxGetData(out[0])) = self;
}

void ClassD_deconstructor_21(int nargout, mxArray *out[], int nargin, const mxArray *in[])
{
  typedef boost::shared_ptr<ClassD> Shared;
  checkArguments("delete_ClassD",nargout,nargin,1);
  Shared *self = *reinterpret_cast<Shared**>(mxGetData(in[0]));
  Collector_ClassD::iterator item;
  item = collector_ClassD.find(self);
  if(item != collector_ClassD.end()) {
    delete self;
    collector_ClassD.erase(item);
  }
}

void ns1aGlobalFunction_22(int nargout, mxArray *out[], int nargin, const mxArray *in[])
{
  checkArguments("ns1aGlobalFunction",nargout,nargin,0);
  out[0] = wrap< Vector >(ns1::aGlobalFunction());
}

void ns2aGlobalFunction_23(int nargout, mxArray *out[], int nargin, const mxArray *in[])
{
  checkArguments("ns2aGlobalFunction",nargout,nargin,0);
  out[0] = wrap< Vector >(ns2::aGlobalFunction());
}
void ns2overloadedGlobalFunction_24(int nargout, mxArray *out[], int nargin, const mxArray *in[])
{
  typedef boost::shared_ptr<ns1::ClassA> SharedClassA;
  checkArguments("ns2overloadedGlobalFunction",nargout,nargin,1);
  ns1::ClassA& a = *unwrap_shared_ptr< ns1::ClassA >(in[0], "ptr_ns1ClassA");
  out[0] = wrap_shared_ptr(SharedClassA(new ns1::ClassA(ns2::overloadedGlobalFunction(a))),"ns1.ClassA", false);
}
void ns2overloadedGlobalFunction_25(int nargout, mxArray *out[], int nargin, const mxArray *in[])
{
  typedef boost::shared_ptr<ns1::ClassA> SharedClassA;
  checkArguments("ns2overloadedGlobalFunction",nargout,nargin,2);
  ns1::ClassA& a = *unwrap_shared_ptr< ns1::ClassA >(in[0], "ptr_ns1ClassA");
  double b = unwrap< double >(in[1]);
  out[0] = wrap_shared_ptr(SharedClassA(new ns1::ClassA(ns2::overloadedGlobalFunction(a,b))),"ns1.ClassA", false);
}

void mexFunction(int nargout, mxArray *out[], int nargin, const mxArray *in[])
{
  mstream mout;
  std::streambuf *outbuf = std::cout.rdbuf(&mout);

  _testNamespaces_RTTIRegister();

  int id = unwrap<int>(in[0]);

  try {
    switch(id) {
    case 0:
      ns1ClassA_collectorInsertAndMakeBase_0(nargout, out, nargin-1, in+1);
      break;
    case 1:
      ns1ClassA_constructor_1(nargout, out, nargin-1, in+1);
      break;
    case 2:
      ns1ClassA_deconstructor_2(nargout, out, nargin-1, in+1);
      break;
    case 3:
      ns1ClassB_collectorInsertAndMakeBase_3(nargout, out, nargin-1, in+1);
      break;
    case 4:
      ns1ClassB_constructor_4(nargout, out, nargin-1, in+1);
      break;
    case 5:
      ns1ClassB_deconstructor_5(nargout, out, nargin-1, in+1);
      break;
    case 6:
      ns2ClassA_collectorInsertAndMakeBase_6(nargout, out, nargin-1, in+1);
      break;
    case 7:
      ns2ClassA_constructor_7(nargout, out, nargin-1, in+1);
      break;
    case 8:
      ns2ClassA_deconstructor_8(nargout, out, nargin-1, in+1);
      break;
    case 9:
      ns2ClassA_memberFunction_9(nargout, out, nargin-1, in+1);
      break;
    case 10:
      ns2ClassA_nsArg_10(nargout, out, nargin-1, in+1);
      break;
    case 11:
      ns2ClassA_nsReturn_11(nargout, out, nargin-1, in+1);
      break;
    case 12:
      ns2ClassA_afunction_12(nargout, out, nargin-1, in+1);
      break;
    case 13:
      ns2ns3ClassB_collectorInsertAndMakeBase_13(nargout, out, nargin-1, in+1);
      break;
    case 14:
      ns2ns3ClassB_constructor_14(nargout, out, nargin-1, in+1);
      break;
    case 15:
      ns2ns3ClassB_deconstructor_15(nargout, out, nargin-1, in+1);
      break;
    case 16:
      ns2ClassC_collectorInsertAndMakeBase_16(nargout, out, nargin-1, in+1);
      break;
    case 17:
      ns2ClassC_constructor_17(nargout, out, nargin-1, in+1);
      break;
    case 18:
      ns2ClassC_deconstructor_18(nargout, out, nargin-1, in+1);
      break;
    case 19:
      ClassD_collectorInsertAndMakeBase_19(nargout, out, nargin-1, in+1);
      break;
    case 20:
      ClassD_constructor_20(nargout, out, nargin-1, in+1);
      break;
    case 21:
      ClassD_deconstructor_21(nargout, out, nargin-1, in+1);
      break;
    case 22:
      ns1aGlobalFunction_22(nargout, out, nargin-1, in+1);
      break;
    case 23:
      ns2aGlobalFunction_23(nargout, out, nargin-1, in+1);
      break;
    case 24:
      ns2overloadedGlobalFunction_24(nargout, out, nargin-1, in+1);
      break;
    case 25:
      ns2overloadedGlobalFunction_25(nargout, out, nargin-1, in+1);
      break;
    }
  } catch(const std::exception& e) {
    mexErrMsgTxt(("Exception from gtsam:\n" + std::string(e.what()) + "\n").c_str());
  }

  std::cout.rdbuf(outbuf);
}
