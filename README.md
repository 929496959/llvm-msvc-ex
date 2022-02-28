# How to compile

```batch
X86：clang+lld+debug
    
mkdir build-debug-64
pushd build-debug-64
cmake .. -G "Visual Studio 16 2019" -A X64 -DLLVM_ENABLE_PROJECTS="clang;lld" -DCMAKE_INSTALL_PREFIX=E:\llvm\install-debug-64 -DLLVM_TARGETS_TO_BUILD=X86 -DCMAKE_BUILD_TYPE=Debug -DHAVE_STD_IS_TRIVIALLY_COPYABLE=0 -DLLVM_TOOL_LLVM_SHLIB_BUILD=off ../llvm
msbuild /m -p:Configuration=Debug INSTALL.vcxproj

X86：clang+lld+release

mkdir build-release-64
pushd build-release-64
cmake .. -G "Visual Studio 16 2019" -A X64 -DLLVM_ENABLE_PROJECTS="clang;lld" -DCMAKE_INSTALL_PREFIX=E:\llvm\install-release-64 -DLLVM_ENABLE_LIBXML2=ON -DLLVM_TARGETS_TO_BUILD=X86 -DCMAKE_BUILD_TYPE=RelWithDebInfo -DLLVM_USE_CRT_RELEASE=MT -DHAVE_STD_IS_TRIVIALLY_COPYABLE=0 -DLLVM_TOOL_LLVM_SHLIB_BUILD=off ../llvm
msbuild /m -p:Configuration=RelWithDebInfo INSTALL.vcxproj 

X86：clang+lld+debug+PatchMan:
cmake .. -G "Visual Studio 16 2019" -A X64 -DLLVM_ENABLE_PROJECTS="clang;lld" -DCMAKE_INSTALL_PREFIX=E:\llvm\install-debug-64 -DLLVM_TARGETS_TO_BUILD=X86 -DCMAKE_BUILD_TYPE=Debug -DHAVE_STD_IS_TRIVIALLY_COPYABLE=0 -DLLVM_TOOL_LLVM_SHLIB_BUILD=off -DLLVM_ENABLE_PATCHMAN=true ../llvm

X86：clang+lld+release+PatchMan:
cmake .. -G "Visual Studio 16 2019" -A X64 -DLLVM_ENABLE_PROJECTS="clang;lld" -DCMAKE_INSTALL_PREFIX=E:\llvm\install-release-64 -DLLVM_ENABLE_LIBXML2=ON -DLLVM_TARGETS_TO_BUILD=X86 -DCMAKE_BUILD_TYPE=RelWithDebInfo -DLLVM_USE_CRT_RELEASE=MT -DHAVE_STD_IS_TRIVIALLY_COPYABLE=0 -DLLVM_TOOL_LLVM_SHLIB_BUILD=off -DLLVM_ENABLE_PATCHMAN=true ../llvm

```
