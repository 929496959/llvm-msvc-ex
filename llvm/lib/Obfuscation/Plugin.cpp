#include "BogusControlFlow.h"
#include "ConstObfuscation.h"
#include "DataObfuscation.h"
#include "Flattening.h"
#include "IndirectCall.h"
#include "MBAObfuscation.h"
#include "SplitBasicBlock.h"
#include "StringObfuscation.h"
#include "Substitution.h"
#include "VMFlatten.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"

using namespace llvm;

llvm::PassPluginLibraryInfo getObfuscationPluginInfo() {
  return {
      LLVM_PLUGIN_API_VERSION, "Obfuscation", LLVM_VERSION_STRING,
      [](PassBuilder &PB) {
        PB.registerPipelineStartEPCallback([](llvm::ModulePassManager &MPM,
                                              OptimizationLevel Level) {
          MPM.addPass(createModuleToFunctionPassAdaptor(SplitBasicBlockPass()));
          MPM.addPass(
              createModuleToFunctionPassAdaptor(BogusControlFlowPass()));
          MPM.addPass(createModuleToFunctionPassAdaptor(SubstitutionPass()));
          MPM.addPass(createModuleToFunctionPassAdaptor(FlatteningPass()));
        });
        PB.registerOptimizerEarlyEPCallback([](llvm::ModulePassManager &MPM,
                                               OptimizationLevel Level) {
          MPM.addPass(StringObfuscationPass());
          MPM.addPass(createModuleToFunctionPassAdaptor(DataObfuscationPass()));
        });

        PB.registerOptimizerLastEPCallback([](llvm::ModulePassManager &MPM,
                                              OptimizationLevel Level) {

          MPM.addPass(ConstObfuscationPass());
          MPM.addPass(createModuleToFunctionPassAdaptor(IndirectCallPass()));
          MPM.addPass(createModuleToFunctionPassAdaptor(MBAObfuscationPass()));
          MPM.addPass(
              createModuleToFunctionPassAdaptor(VmFlatObfuscationPass()));
        });
        //PB.registerVectorizerStartEPCallback(
        //    [](FunctionPassManager &FPM, OptimizationLevel Level) {});
      }};
}

#ifndef LLVM_OBFUSCATION_LINK_INTO_TOOLS
extern "C" LLVM_ATTRIBUTE_WEAK ::llvm::PassPluginLibraryInfo
llvmGetPassPluginInfo() {
  return getObfuscationPluginInfo();
}
#endif
