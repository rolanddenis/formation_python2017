#define BOOST_SIMD_NO_STRICT_ALIASING 1
#include <pythonic/core.hpp>
#include <pythonic/python/core.hpp>
#include <pythonic/types/bool.hpp>
#include <pythonic/types/int.hpp>
#ifdef _OPENMP
#include <omp.h>
#endif
#include <pythonic/include/types/float64.hpp>
#include <pythonic/include/types/numpy_texpr.hpp>
#include <pythonic/include/types/ndarray.hpp>
#include <pythonic/types/numpy_texpr.hpp>
#include <pythonic/types/float64.hpp>
#include <pythonic/types/ndarray.hpp>
#include <pythonic/include/__builtin__/tuple.hpp>
#include <pythonic/include/numpy/abs.hpp>
#include <pythonic/include/__builtin__/range.hpp>
#include <pythonic/include/operator_/div.hpp>
#include <pythonic/include/numpy/empty.hpp>
#include <pythonic/include/numpy/max.hpp>
#include <pythonic/include/__builtin__/max.hpp>
#include <pythonic/include/__builtin__/getattr.hpp>
#include <pythonic/include/numpy/zeros.hpp>
#include <pythonic/include/__builtin__/str.hpp>
#include <pythonic/__builtin__/tuple.hpp>
#include <pythonic/numpy/abs.hpp>
#include <pythonic/__builtin__/range.hpp>
#include <pythonic/operator_/div.hpp>
#include <pythonic/numpy/empty.hpp>
#include <pythonic/numpy/max.hpp>
#include <pythonic/__builtin__/max.hpp>
#include <pythonic/__builtin__/getattr.hpp>
#include <pythonic/numpy/zeros.hpp>
#include <pythonic/__builtin__/str.hpp>
namespace __pythran_kernels
{
  struct convolve_matrix3
  {
    typedef void callable;
    typedef void pure;
    template <typename argument_type0 , typename argument_type1 >
    struct type
    {
      typedef typename pythonic::assignable<decltype(pythonic::__builtin__::getattr<pythonic::types::attr::SHAPE>(std::declval<typename std::remove_cv<typename std::remove_reference<argument_type0>::type>::type>()))>::type __type0;
      typedef typename std::tuple_element<0,typename std::remove_reference<__type0>::type>::type __type1;
      typedef decltype(pythonic::__builtin__::getattr<pythonic::types::attr::SHAPE>(std::declval<typename std::remove_cv<typename std::remove_reference<argument_type1>::type>::type>())) __type2;
      typedef typename pythonic::lazy<typename std::tuple_element<0,typename std::remove_reference<__type2>::type>::type>::type __type3;
      typedef decltype((std::declval<__type1>() - std::declval<__type3>())) __type4;
      typedef long __type5;
      typedef decltype((std::declval<__type4>() + std::declval<__type5>())) __type6;
      typedef typename std::tuple_element<1,typename std::remove_reference<__type0>::type>::type __type7;
      typedef typename pythonic::lazy<typename std::tuple_element<1,typename std::remove_reference<__type2>::type>::type>::type __type9;
      typedef decltype((std::declval<__type7>() - std::declval<__type9>())) __type10;
      typedef decltype((std::declval<__type10>() + std::declval<__type5>())) __type12;
      typedef typename std::tuple_element<2,typename std::remove_reference<__type0>::type>::type __type13;
      typedef decltype(pythonic::types::make_tuple(std::declval<__type6>(), std::declval<__type12>(), std::declval<__type13>())) __type14;
      typedef typename pythonic::assignable<decltype(std::declval<typename std::remove_cv<typename std::remove_reference<decltype(pythonic::numpy::functor::zeros{})>::type>::type>()(std::declval<__type14>()))>::type __type15;
      typedef typename std::remove_cv<typename std::remove_reference<argument_type1>::type>::type __type16;
      typedef decltype(std::declval<typename std::remove_cv<typename std::remove_reference<decltype(pythonic::__builtin__::functor::range{})>::type>::type>()(std::declval<__type5>(), std::declval<__type9>())) __type18;
      typedef typename std::remove_cv<typename std::iterator_traits<typename std::remove_reference<__type18>::type::iterator>::value_type>::type __type19;
      typedef decltype(std::declval<typename std::remove_cv<typename std::remove_reference<decltype(pythonic::__builtin__::functor::range{})>::type>::type>()(std::declval<__type5>(), std::declval<__type3>())) __type21;
      typedef typename std::remove_cv<typename std::iterator_traits<typename std::remove_reference<__type21>::type::iterator>::value_type>::type __type22;
      typedef decltype(pythonic::types::make_tuple(std::declval<__type19>(), std::declval<__type22>())) __type23;
      typedef decltype(std::declval<__type16>()[std::declval<__type23>()]) __type24;
      typedef typename std::remove_cv<typename std::remove_reference<argument_type0>::type>::type __type25;
      typedef pythonic::types::contiguous_slice __type26;
      typedef decltype(std::declval<__type25>()(std::declval<__type26>(), std::declval<__type26>(), std::declval<__type26>())) __type29;
      typedef decltype((std::declval<__type24>() * std::declval<__type29>())) __type30;
      typedef container<typename std::remove_reference<__type30>::type> __type31;
      typedef typename __combined<__type15,__type31>::type __type32;
      typedef typename pythonic::assignable<decltype(std::declval<typename std::remove_cv<typename std::remove_reference<decltype(pythonic::numpy::functor::abs{})>::type>::type>()(std::declval<__type32>()))>::type __type33;
      typedef double __type34;
      typedef decltype(std::declval<typename std::remove_cv<typename std::remove_reference<decltype(pythonic::numpy::functor::max{})>::type>::type>()(std::declval<__type33>())) __type36;
      typedef decltype(std::declval<typename std::remove_cv<typename std::remove_reference<decltype(pythonic::__builtin__::functor::max{})>::type>::type>()(std::declval<__type34>(), std::declval<__type36>())) __type37;
      typedef decltype((std::declval<__type37>() + std::declval<__type34>())) __type39;
      typedef decltype((pythonic::operator_::div(std::declval<__type34>(), std::declval<__type39>()))) __type40;
      typedef decltype((std::declval<__type33>() * std::declval<__type40>())) __type41;
      typedef typename pythonic::returnable<typename __combined<__type33,__type40,__type41>::type>::type result_type;
    }  
    ;
    template <typename argument_type0 , typename argument_type1 >
    typename type<argument_type0, argument_type1>::result_type operator()(argument_type0 const & image, argument_type1 const & convolution_array) const
    ;
  }  ;
  struct convolve_matrix2
  {
    typedef void callable;
    typedef void pure;
    template <typename argument_type0 , typename argument_type1 >
    struct type
    {
      typedef typename pythonic::assignable<decltype(pythonic::__builtin__::getattr<pythonic::types::attr::SHAPE>(std::declval<typename std::remove_cv<typename std::remove_reference<argument_type0>::type>::type>()))>::type __type0;
      typedef typename std::tuple_element<0,typename std::remove_reference<__type0>::type>::type __type1;
      typedef decltype(pythonic::__builtin__::getattr<pythonic::types::attr::SHAPE>(std::declval<typename std::remove_cv<typename std::remove_reference<argument_type1>::type>::type>())) __type2;
      typedef typename pythonic::lazy<typename std::tuple_element<0,typename std::remove_reference<__type2>::type>::type>::type __type3;
      typedef decltype((std::declval<__type1>() - std::declval<__type3>())) __type4;
      typedef long __type5;
      typedef decltype((std::declval<__type4>() + std::declval<__type5>())) __type6;
      typedef typename std::tuple_element<1,typename std::remove_reference<__type0>::type>::type __type7;
      typedef typename pythonic::lazy<typename std::tuple_element<1,typename std::remove_reference<__type2>::type>::type>::type __type9;
      typedef decltype((std::declval<__type7>() - std::declval<__type9>())) __type10;
      typedef decltype((std::declval<__type10>() + std::declval<__type5>())) __type12;
      typedef decltype(pythonic::types::make_tuple(std::declval<__type6>(), std::declval<__type12>())) __type13;
      typedef typename pythonic::assignable<decltype(std::declval<typename std::remove_cv<typename std::remove_reference<decltype(pythonic::numpy::functor::zeros{})>::type>::type>()(std::declval<__type13>()))>::type __type14;
      typedef typename std::remove_cv<typename std::remove_reference<argument_type1>::type>::type __type15;
      typedef decltype(std::declval<typename std::remove_cv<typename std::remove_reference<decltype(pythonic::__builtin__::functor::range{})>::type>::type>()(std::declval<__type5>(), std::declval<__type9>())) __type17;
      typedef typename std::remove_cv<typename std::iterator_traits<typename std::remove_reference<__type17>::type::iterator>::value_type>::type __type18;
      typedef decltype(std::declval<typename std::remove_cv<typename std::remove_reference<decltype(pythonic::__builtin__::functor::range{})>::type>::type>()(std::declval<__type5>(), std::declval<__type3>())) __type20;
      typedef typename std::remove_cv<typename std::iterator_traits<typename std::remove_reference<__type20>::type::iterator>::value_type>::type __type21;
      typedef decltype(pythonic::types::make_tuple(std::declval<__type18>(), std::declval<__type21>())) __type22;
      typedef decltype(std::declval<__type15>()[std::declval<__type22>()]) __type23;
      typedef typename std::remove_cv<typename std::remove_reference<argument_type0>::type>::type __type24;
      typedef pythonic::types::contiguous_slice __type25;
      typedef decltype(std::declval<__type24>()(std::declval<__type25>(), std::declval<__type25>())) __type27;
      typedef decltype((std::declval<__type23>() * std::declval<__type27>())) __type28;
      typedef container<typename std::remove_reference<__type28>::type> __type29;
      typedef typename __combined<__type14,__type29>::type __type30;
      typedef typename pythonic::assignable<decltype(std::declval<typename std::remove_cv<typename std::remove_reference<decltype(pythonic::numpy::functor::abs{})>::type>::type>()(std::declval<__type30>()))>::type __type31;
      typedef double __type32;
      typedef decltype(std::declval<typename std::remove_cv<typename std::remove_reference<decltype(pythonic::numpy::functor::max{})>::type>::type>()(std::declval<__type31>())) __type34;
      typedef decltype(std::declval<typename std::remove_cv<typename std::remove_reference<decltype(pythonic::__builtin__::functor::max{})>::type>::type>()(std::declval<__type32>(), std::declval<__type34>())) __type35;
      typedef decltype((std::declval<__type35>() + std::declval<__type32>())) __type37;
      typedef decltype((pythonic::operator_::div(std::declval<__type32>(), std::declval<__type37>()))) __type38;
      typedef decltype((std::declval<__type31>() * std::declval<__type38>())) __type39;
      typedef typename pythonic::returnable<typename __combined<__type31,__type38,__type39>::type>::type result_type;
    }  
    ;
    template <typename argument_type0 , typename argument_type1 >
    typename type<argument_type0, argument_type1>::result_type operator()(argument_type0 const & image, argument_type1 const & convolution_array) const
    ;
  }  ;
  struct convolve_laplacien3
  {
    typedef void callable;
    typedef void pure;
    template <typename argument_type0 >
    struct type
    {
      typedef typename pythonic::assignable<decltype(pythonic::__builtin__::getattr<pythonic::types::attr::SHAPE>(std::declval<typename std::remove_cv<typename std::remove_reference<argument_type0>::type>::type>()))>::type __type0;
      typedef typename std::tuple_element<0,typename std::remove_reference<__type0>::type>::type __type1;
      typedef long __type2;
      typedef decltype((std::declval<__type1>() - std::declval<__type2>())) __type3;
      typedef typename std::tuple_element<1,typename std::remove_reference<__type0>::type>::type __type4;
      typedef decltype((std::declval<__type4>() - std::declval<__type2>())) __type6;
      typedef typename std::tuple_element<2,typename std::remove_reference<__type0>::type>::type __type7;
      typedef decltype(pythonic::types::make_tuple(std::declval<__type3>(), std::declval<__type6>(), std::declval<__type7>())) __type8;
      typedef typename pythonic::assignable<decltype(std::declval<typename std::remove_cv<typename std::remove_reference<decltype(pythonic::numpy::functor::empty{})>::type>::type>()(std::declval<__type8>()))>::type __type9;
      typedef double __type10;
      typedef typename std::remove_cv<typename std::remove_reference<argument_type0>::type>::type __type13;
      typedef pythonic::types::contiguous_slice __type14;
      typedef decltype(std::declval<__type13>()(std::declval<__type14>(), std::declval<__type14>(), std::declval<__type14>())) __type17;
      typedef decltype((std::declval<__type2>() * std::declval<__type17>())) __type18;
      typedef decltype((std::declval<__type18>() - std::declval<__type17>())) __type23;
      typedef decltype((std::declval<__type23>() - std::declval<__type17>())) __type28;
      typedef decltype((std::declval<__type28>() - std::declval<__type17>())) __type33;
      typedef decltype((std::declval<__type33>() - std::declval<__type17>())) __type38;
      typedef decltype(std::declval<typename std::remove_cv<typename std::remove_reference<decltype(pythonic::numpy::functor::abs{})>::type>::type>()(std::declval<__type38>())) __type39;
      typedef container<typename std::remove_reference<__type39>::type> __type40;
      typedef typename __combined<__type9,__type40>::type __type41;
      typedef decltype(std::declval<typename std::remove_cv<typename std::remove_reference<decltype(pythonic::numpy::functor::max{})>::type>::type>()(std::declval<__type41>())) __type42;
      typedef decltype(std::declval<typename std::remove_cv<typename std::remove_reference<decltype(pythonic::__builtin__::functor::max{})>::type>::type>()(std::declval<__type10>(), std::declval<__type42>())) __type43;
      typedef decltype((std::declval<__type43>() + std::declval<__type10>())) __type45;
      typedef decltype((pythonic::operator_::div(std::declval<__type10>(), std::declval<__type45>()))) __type46;
      typedef decltype((std::declval<__type9>() * std::declval<__type46>())) __type47;
      typedef typename pythonic::returnable<typename __combined<__type9,__type46,__type47,__type40>::type>::type result_type;
    }  
    ;
    template <typename argument_type0 >
    typename type<argument_type0>::result_type operator()(argument_type0 const & image) const
    ;
  }  ;
  struct convolve_laplacien2
  {
    typedef void callable;
    typedef void pure;
    template <typename argument_type0 >
    struct type
    {
      typedef typename pythonic::assignable<decltype(pythonic::__builtin__::getattr<pythonic::types::attr::SHAPE>(std::declval<typename std::remove_cv<typename std::remove_reference<argument_type0>::type>::type>()))>::type __type0;
      typedef typename std::tuple_element<0,typename std::remove_reference<__type0>::type>::type __type1;
      typedef long __type2;
      typedef decltype((std::declval<__type1>() - std::declval<__type2>())) __type3;
      typedef typename std::tuple_element<1,typename std::remove_reference<__type0>::type>::type __type4;
      typedef decltype((std::declval<__type4>() - std::declval<__type2>())) __type6;
      typedef decltype(pythonic::types::make_tuple(std::declval<__type3>(), std::declval<__type6>())) __type7;
      typedef typename pythonic::assignable<decltype(std::declval<typename std::remove_cv<typename std::remove_reference<decltype(pythonic::numpy::functor::empty{})>::type>::type>()(std::declval<__type7>()))>::type __type8;
      typedef double __type9;
      typedef typename std::remove_cv<typename std::remove_reference<argument_type0>::type>::type __type12;
      typedef pythonic::types::contiguous_slice __type13;
      typedef decltype(std::declval<__type12>()(std::declval<__type13>(), std::declval<__type13>())) __type15;
      typedef decltype((std::declval<__type2>() * std::declval<__type15>())) __type16;
      typedef decltype((std::declval<__type16>() - std::declval<__type15>())) __type20;
      typedef decltype((std::declval<__type20>() - std::declval<__type15>())) __type24;
      typedef decltype((std::declval<__type24>() - std::declval<__type15>())) __type28;
      typedef decltype((std::declval<__type28>() - std::declval<__type15>())) __type32;
      typedef decltype(std::declval<typename std::remove_cv<typename std::remove_reference<decltype(pythonic::numpy::functor::abs{})>::type>::type>()(std::declval<__type32>())) __type33;
      typedef container<typename std::remove_reference<__type33>::type> __type34;
      typedef typename __combined<__type8,__type34>::type __type35;
      typedef decltype(std::declval<typename std::remove_cv<typename std::remove_reference<decltype(pythonic::numpy::functor::max{})>::type>::type>()(std::declval<__type35>())) __type36;
      typedef decltype(std::declval<typename std::remove_cv<typename std::remove_reference<decltype(pythonic::__builtin__::functor::max{})>::type>::type>()(std::declval<__type9>(), std::declval<__type36>())) __type37;
      typedef decltype((std::declval<__type37>() + std::declval<__type9>())) __type39;
      typedef decltype((pythonic::operator_::div(std::declval<__type9>(), std::declval<__type39>()))) __type40;
      typedef decltype((std::declval<__type8>() * std::declval<__type40>())) __type41;
      typedef typename pythonic::returnable<typename __combined<__type8,__type40,__type41,__type34>::type>::type result_type;
    }  
    ;
    template <typename argument_type0 >
    typename type<argument_type0>::result_type operator()(argument_type0 const & image) const
    ;
  }  ;
  struct convolve_mean3
  {
    typedef void callable;
    typedef void pure;
    template <typename argument_type0 >
    struct type
    {
      typedef typename pythonic::assignable<decltype(pythonic::__builtin__::getattr<pythonic::types::attr::SHAPE>(std::declval<typename std::remove_cv<typename std::remove_reference<argument_type0>::type>::type>()))>::type __type0;
      typedef typename std::tuple_element<0,typename std::remove_reference<__type0>::type>::type __type1;
      typedef long __type2;
      typedef decltype((std::declval<__type1>() - std::declval<__type2>())) __type3;
      typedef typename std::tuple_element<1,typename std::remove_reference<__type0>::type>::type __type4;
      typedef decltype((std::declval<__type4>() - std::declval<__type2>())) __type6;
      typedef typename std::tuple_element<2,typename std::remove_reference<__type0>::type>::type __type7;
      typedef decltype(pythonic::types::make_tuple(std::declval<__type3>(), std::declval<__type6>(), std::declval<__type7>())) __type8;
      typedef typename pythonic::assignable<decltype(std::declval<typename std::remove_cv<typename std::remove_reference<decltype(pythonic::numpy::functor::empty{})>::type>::type>()(std::declval<__type8>()))>::type __type9;
      typedef double __type10;
      typedef typename std::remove_cv<typename std::remove_reference<argument_type0>::type>::type __type11;
      typedef pythonic::types::contiguous_slice __type12;
      typedef decltype(std::declval<__type11>()(std::declval<__type12>(), std::declval<__type12>(), std::declval<__type12>())) __type15;
      typedef decltype((std::declval<__type15>() + std::declval<__type15>())) __type20;
      typedef decltype((std::declval<__type20>() + std::declval<__type15>())) __type25;
      typedef decltype((std::declval<__type25>() + std::declval<__type15>())) __type30;
      typedef decltype((std::declval<__type10>() * std::declval<__type30>())) __type31;
      typedef container<typename std::remove_reference<__type31>::type> __type32;
      typedef typename pythonic::returnable<typename __combined<__type9,__type32>::type>::type result_type;
    }  
    ;
    template <typename argument_type0 >
    typename type<argument_type0>::result_type operator()(argument_type0 const & image) const
    ;
  }  ;
  struct convolve_mean2
  {
    typedef void callable;
    typedef void pure;
    template <typename argument_type0 >
    struct type
    {
      typedef typename pythonic::assignable<decltype(pythonic::__builtin__::getattr<pythonic::types::attr::SHAPE>(std::declval<typename std::remove_cv<typename std::remove_reference<argument_type0>::type>::type>()))>::type __type0;
      typedef typename std::tuple_element<0,typename std::remove_reference<__type0>::type>::type __type1;
      typedef long __type2;
      typedef decltype((std::declval<__type1>() - std::declval<__type2>())) __type3;
      typedef typename std::tuple_element<1,typename std::remove_reference<__type0>::type>::type __type4;
      typedef decltype((std::declval<__type4>() - std::declval<__type2>())) __type6;
      typedef decltype(pythonic::types::make_tuple(std::declval<__type3>(), std::declval<__type6>())) __type7;
      typedef typename pythonic::assignable<decltype(std::declval<typename std::remove_cv<typename std::remove_reference<decltype(pythonic::numpy::functor::empty{})>::type>::type>()(std::declval<__type7>()))>::type __type8;
      typedef double __type9;
      typedef typename std::remove_cv<typename std::remove_reference<argument_type0>::type>::type __type10;
      typedef pythonic::types::contiguous_slice __type11;
      typedef decltype(std::declval<__type10>()(std::declval<__type11>(), std::declval<__type11>())) __type13;
      typedef decltype((std::declval<__type13>() + std::declval<__type13>())) __type17;
      typedef decltype((std::declval<__type17>() + std::declval<__type13>())) __type21;
      typedef decltype((std::declval<__type21>() + std::declval<__type13>())) __type25;
      typedef decltype((std::declval<__type9>() * std::declval<__type25>())) __type26;
      typedef container<typename std::remove_reference<__type26>::type> __type27;
      typedef typename pythonic::returnable<typename __combined<__type8,__type27>::type>::type result_type;
    }  
    ;
    template <typename argument_type0 >
    typename type<argument_type0>::result_type operator()(argument_type0 const & image) const
    ;
  }  ;
  template <typename argument_type0 , typename argument_type1 >
  typename convolve_matrix3::type<argument_type0, argument_type1>::result_type convolve_matrix3::operator()(argument_type0 const & image, argument_type1 const & convolution_array) const
  {
    typedef typename pythonic::assignable<decltype(pythonic::__builtin__::getattr<pythonic::types::attr::SHAPE>(std::declval<typename std::remove_cv<typename std::remove_reference<argument_type0>::type>::type>()))>::type __type0;
    typedef typename std::tuple_element<0,typename std::remove_reference<__type0>::type>::type __type1;
    typedef decltype(pythonic::__builtin__::getattr<pythonic::types::attr::SHAPE>(std::declval<typename std::remove_cv<typename std::remove_reference<argument_type1>::type>::type>())) __type2;
    typedef typename pythonic::lazy<typename std::tuple_element<0,typename std::remove_reference<__type2>::type>::type>::type __type3;
    typedef decltype((std::declval<__type1>() - std::declval<__type3>())) __type4;
    typedef long __type5;
    typedef decltype((std::declval<__type4>() + std::declval<__type5>())) __type6;
    typedef typename std::tuple_element<1,typename std::remove_reference<__type0>::type>::type __type7;
    typedef typename pythonic::lazy<typename std::tuple_element<1,typename std::remove_reference<__type2>::type>::type>::type __type9;
    typedef decltype((std::declval<__type7>() - std::declval<__type9>())) __type10;
    typedef decltype((std::declval<__type10>() + std::declval<__type5>())) __type12;
    typedef typename std::tuple_element<2,typename std::remove_reference<__type0>::type>::type __type13;
    typedef decltype(pythonic::types::make_tuple(std::declval<__type6>(), std::declval<__type12>(), std::declval<__type13>())) __type14;
    typedef typename pythonic::assignable<decltype(std::declval<typename std::remove_cv<typename std::remove_reference<decltype(pythonic::numpy::functor::zeros{})>::type>::type>()(std::declval<__type14>()))>::type __type15;
    typedef typename std::remove_cv<typename std::remove_reference<argument_type1>::type>::type __type16;
    typedef decltype(std::declval<typename std::remove_cv<typename std::remove_reference<decltype(pythonic::__builtin__::functor::range{})>::type>::type>()(std::declval<__type5>(), std::declval<__type9>())) __type18;
    typedef typename std::remove_cv<typename std::iterator_traits<typename std::remove_reference<__type18>::type::iterator>::value_type>::type __type19;
    typedef decltype(std::declval<typename std::remove_cv<typename std::remove_reference<decltype(pythonic::__builtin__::functor::range{})>::type>::type>()(std::declval<__type5>(), std::declval<__type3>())) __type21;
    typedef typename std::remove_cv<typename std::iterator_traits<typename std::remove_reference<__type21>::type::iterator>::value_type>::type __type22;
    typedef decltype(pythonic::types::make_tuple(std::declval<__type19>(), std::declval<__type22>())) __type23;
    typedef decltype(std::declval<__type16>()[std::declval<__type23>()]) __type24;
    typedef typename std::remove_cv<typename std::remove_reference<argument_type0>::type>::type __type25;
    typedef pythonic::types::contiguous_slice __type26;
    typedef decltype(std::declval<__type25>()(std::declval<__type26>(), std::declval<__type26>(), std::declval<__type26>())) __type29;
    typedef decltype((std::declval<__type24>() * std::declval<__type29>())) __type30;
    typedef container<typename std::remove_reference<__type30>::type> __type31;
    typedef typename __combined<__type15,__type31>::type __type32;
    typedef typename pythonic::assignable<decltype(std::declval<typename std::remove_cv<typename std::remove_reference<decltype(pythonic::numpy::functor::abs{})>::type>::type>()(std::declval<__type32>()))>::type __type33;
    typedef double __type34;
    typedef decltype(std::declval<typename std::remove_cv<typename std::remove_reference<decltype(pythonic::numpy::functor::max{})>::type>::type>()(std::declval<__type33>())) __type36;
    typedef decltype(std::declval<typename std::remove_cv<typename std::remove_reference<decltype(pythonic::__builtin__::functor::max{})>::type>::type>()(std::declval<__type34>(), std::declval<__type36>())) __type37;
    typedef decltype((std::declval<__type37>() + std::declval<__type34>())) __type39;
    typedef decltype((pythonic::operator_::div(std::declval<__type34>(), std::declval<__type39>()))) __type40;
    typedef decltype((std::declval<__type33>() * std::declval<__type40>())) __type41;
    typename pythonic::assignable<decltype(pythonic::__builtin__::getattr<pythonic::types::attr::SHAPE>(image))>::type __tuple0 = pythonic::__builtin__::getattr<pythonic::types::attr::SHAPE>(image);
    ;
    ;
    ;
    typename pythonic::lazy<decltype(std::get<0>(pythonic::__builtin__::getattr<pythonic::types::attr::SHAPE>(convolution_array)))>::type nx = std::get<0>(pythonic::__builtin__::getattr<pythonic::types::attr::SHAPE>(convolution_array));
    typename pythonic::lazy<decltype(std::get<1>(pythonic::__builtin__::getattr<pythonic::types::attr::SHAPE>(convolution_array)))>::type ny = std::get<1>(pythonic::__builtin__::getattr<pythonic::types::attr::SHAPE>(convolution_array));
    ;
    ;
    typename pythonic::assignable<typename __combined<__type15,__type31>::type>::type out_image = pythonic::numpy::functor::zeros{}(pythonic::types::make_tuple(((std::get<0>(__tuple0) - nx) + 1L), ((std::get<1>(__tuple0) - ny) + 1L), std::get<2>(__tuple0)));
    typename pythonic::assignable<decltype(pythonic::__builtin__::getattr<pythonic::types::attr::SHAPE>(out_image))>::type __tuple1 = pythonic::__builtin__::getattr<pythonic::types::attr::SHAPE>(out_image);
    typename pythonic::assignable<decltype(std::get<0>(__tuple1))>::type h = std::get<0>(__tuple1);
    typename pythonic::assignable<decltype(std::get<1>(__tuple1))>::type w = std::get<1>(__tuple1);
    ;
    {
      long  __target1 = ny;
      for (long  jw=0L; jw < __target1; jw += 1L)
      {
        {
          long  __target2 = nx;
          for (long  iw=0L; iw < __target2; iw += 1L)
          {
            out_image(pythonic::types::contiguous_slice(pythonic::__builtin__::None,pythonic::__builtin__::None),pythonic::types::contiguous_slice(pythonic::__builtin__::None,pythonic::__builtin__::None),pythonic::types::contiguous_slice(pythonic::__builtin__::None,pythonic::__builtin__::None)) += (convolution_array[pythonic::types::make_tuple(jw, iw)] * image(pythonic::types::contiguous_slice(jw,(jw + h)),pythonic::types::contiguous_slice(iw,(iw + w)),pythonic::types::contiguous_slice(pythonic::__builtin__::None,pythonic::__builtin__::None)));
          }
        }
      }
    }
    typename pythonic::assignable<typename __combined<__type33,__type40,__type41>::type>::type out_image_ = pythonic::numpy::functor::abs{}(out_image);
    ;
    ;
    out_image_ *= (pythonic::operator_::div(1.0, (pythonic::__builtin__::functor::max{}(1.0, pythonic::numpy::functor::max{}(out_image_)) + 1e-09)));
    return out_image_;
  }
  template <typename argument_type0 , typename argument_type1 >
  typename convolve_matrix2::type<argument_type0, argument_type1>::result_type convolve_matrix2::operator()(argument_type0 const & image, argument_type1 const & convolution_array) const
  {
    typedef typename pythonic::assignable<decltype(pythonic::__builtin__::getattr<pythonic::types::attr::SHAPE>(std::declval<typename std::remove_cv<typename std::remove_reference<argument_type0>::type>::type>()))>::type __type0;
    typedef typename std::tuple_element<0,typename std::remove_reference<__type0>::type>::type __type1;
    typedef decltype(pythonic::__builtin__::getattr<pythonic::types::attr::SHAPE>(std::declval<typename std::remove_cv<typename std::remove_reference<argument_type1>::type>::type>())) __type2;
    typedef typename pythonic::lazy<typename std::tuple_element<0,typename std::remove_reference<__type2>::type>::type>::type __type3;
    typedef decltype((std::declval<__type1>() - std::declval<__type3>())) __type4;
    typedef long __type5;
    typedef decltype((std::declval<__type4>() + std::declval<__type5>())) __type6;
    typedef typename std::tuple_element<1,typename std::remove_reference<__type0>::type>::type __type7;
    typedef typename pythonic::lazy<typename std::tuple_element<1,typename std::remove_reference<__type2>::type>::type>::type __type9;
    typedef decltype((std::declval<__type7>() - std::declval<__type9>())) __type10;
    typedef decltype((std::declval<__type10>() + std::declval<__type5>())) __type12;
    typedef decltype(pythonic::types::make_tuple(std::declval<__type6>(), std::declval<__type12>())) __type13;
    typedef typename pythonic::assignable<decltype(std::declval<typename std::remove_cv<typename std::remove_reference<decltype(pythonic::numpy::functor::zeros{})>::type>::type>()(std::declval<__type13>()))>::type __type14;
    typedef typename std::remove_cv<typename std::remove_reference<argument_type1>::type>::type __type15;
    typedef decltype(std::declval<typename std::remove_cv<typename std::remove_reference<decltype(pythonic::__builtin__::functor::range{})>::type>::type>()(std::declval<__type5>(), std::declval<__type9>())) __type17;
    typedef typename std::remove_cv<typename std::iterator_traits<typename std::remove_reference<__type17>::type::iterator>::value_type>::type __type18;
    typedef decltype(std::declval<typename std::remove_cv<typename std::remove_reference<decltype(pythonic::__builtin__::functor::range{})>::type>::type>()(std::declval<__type5>(), std::declval<__type3>())) __type20;
    typedef typename std::remove_cv<typename std::iterator_traits<typename std::remove_reference<__type20>::type::iterator>::value_type>::type __type21;
    typedef decltype(pythonic::types::make_tuple(std::declval<__type18>(), std::declval<__type21>())) __type22;
    typedef decltype(std::declval<__type15>()[std::declval<__type22>()]) __type23;
    typedef typename std::remove_cv<typename std::remove_reference<argument_type0>::type>::type __type24;
    typedef pythonic::types::contiguous_slice __type25;
    typedef decltype(std::declval<__type24>()(std::declval<__type25>(), std::declval<__type25>())) __type27;
    typedef decltype((std::declval<__type23>() * std::declval<__type27>())) __type28;
    typedef container<typename std::remove_reference<__type28>::type> __type29;
    typedef typename __combined<__type14,__type29>::type __type30;
    typedef typename pythonic::assignable<decltype(std::declval<typename std::remove_cv<typename std::remove_reference<decltype(pythonic::numpy::functor::abs{})>::type>::type>()(std::declval<__type30>()))>::type __type31;
    typedef double __type32;
    typedef decltype(std::declval<typename std::remove_cv<typename std::remove_reference<decltype(pythonic::numpy::functor::max{})>::type>::type>()(std::declval<__type31>())) __type34;
    typedef decltype(std::declval<typename std::remove_cv<typename std::remove_reference<decltype(pythonic::__builtin__::functor::max{})>::type>::type>()(std::declval<__type32>(), std::declval<__type34>())) __type35;
    typedef decltype((std::declval<__type35>() + std::declval<__type32>())) __type37;
    typedef decltype((pythonic::operator_::div(std::declval<__type32>(), std::declval<__type37>()))) __type38;
    typedef decltype((std::declval<__type31>() * std::declval<__type38>())) __type39;
    typename pythonic::assignable<decltype(pythonic::__builtin__::getattr<pythonic::types::attr::SHAPE>(image))>::type __tuple0 = pythonic::__builtin__::getattr<pythonic::types::attr::SHAPE>(image);
    ;
    ;
    typename pythonic::lazy<decltype(std::get<0>(pythonic::__builtin__::getattr<pythonic::types::attr::SHAPE>(convolution_array)))>::type nx = std::get<0>(pythonic::__builtin__::getattr<pythonic::types::attr::SHAPE>(convolution_array));
    typename pythonic::lazy<decltype(std::get<1>(pythonic::__builtin__::getattr<pythonic::types::attr::SHAPE>(convolution_array)))>::type ny = std::get<1>(pythonic::__builtin__::getattr<pythonic::types::attr::SHAPE>(convolution_array));
    ;
    ;
    typename pythonic::assignable<typename __combined<__type14,__type29>::type>::type out_image = pythonic::numpy::functor::zeros{}(pythonic::types::make_tuple(((std::get<0>(__tuple0) - nx) + 1L), ((std::get<1>(__tuple0) - ny) + 1L)));
    typename pythonic::assignable<decltype(pythonic::__builtin__::getattr<pythonic::types::attr::SHAPE>(out_image))>::type __tuple1 = pythonic::__builtin__::getattr<pythonic::types::attr::SHAPE>(out_image);
    typename pythonic::assignable<decltype(std::get<0>(__tuple1))>::type h = std::get<0>(__tuple1);
    typename pythonic::assignable<decltype(std::get<1>(__tuple1))>::type w = std::get<1>(__tuple1);
    {
      long  __target1 = ny;
      for (long  jw=0L; jw < __target1; jw += 1L)
      {
        {
          long  __target2 = nx;
          for (long  iw=0L; iw < __target2; iw += 1L)
          {
            out_image(pythonic::types::contiguous_slice(pythonic::__builtin__::None,pythonic::__builtin__::None),pythonic::types::contiguous_slice(pythonic::__builtin__::None,pythonic::__builtin__::None)) += (convolution_array[pythonic::types::make_tuple(jw, iw)] * image(pythonic::types::contiguous_slice(jw,(jw + h)),pythonic::types::contiguous_slice(iw,(iw + w))));
          }
        }
      }
    }
    typename pythonic::assignable<typename __combined<__type31,__type38,__type39>::type>::type out_image_ = pythonic::numpy::functor::abs{}(out_image);
    ;
    ;
    out_image_ *= (pythonic::operator_::div(1.0, (pythonic::__builtin__::functor::max{}(1.0, pythonic::numpy::functor::max{}(out_image_)) + 1e-09)));
    return out_image_;
  }
  template <typename argument_type0 >
  typename convolve_laplacien3::type<argument_type0>::result_type convolve_laplacien3::operator()(argument_type0 const & image) const
  {
    typedef typename pythonic::assignable<decltype(pythonic::__builtin__::getattr<pythonic::types::attr::SHAPE>(std::declval<typename std::remove_cv<typename std::remove_reference<argument_type0>::type>::type>()))>::type __type0;
    typedef typename std::tuple_element<0,typename std::remove_reference<__type0>::type>::type __type1;
    typedef long __type2;
    typedef decltype((std::declval<__type1>() - std::declval<__type2>())) __type3;
    typedef typename std::tuple_element<1,typename std::remove_reference<__type0>::type>::type __type4;
    typedef decltype((std::declval<__type4>() - std::declval<__type2>())) __type6;
    typedef typename std::tuple_element<2,typename std::remove_reference<__type0>::type>::type __type7;
    typedef decltype(pythonic::types::make_tuple(std::declval<__type3>(), std::declval<__type6>(), std::declval<__type7>())) __type8;
    typedef typename pythonic::assignable<decltype(std::declval<typename std::remove_cv<typename std::remove_reference<decltype(pythonic::numpy::functor::empty{})>::type>::type>()(std::declval<__type8>()))>::type __type9;
    typedef double __type10;
    typedef typename std::remove_cv<typename std::remove_reference<argument_type0>::type>::type __type13;
    typedef pythonic::types::contiguous_slice __type14;
    typedef decltype(std::declval<__type13>()(std::declval<__type14>(), std::declval<__type14>(), std::declval<__type14>())) __type17;
    typedef decltype((std::declval<__type2>() * std::declval<__type17>())) __type18;
    typedef decltype((std::declval<__type18>() - std::declval<__type17>())) __type23;
    typedef decltype((std::declval<__type23>() - std::declval<__type17>())) __type28;
    typedef decltype((std::declval<__type28>() - std::declval<__type17>())) __type33;
    typedef decltype((std::declval<__type33>() - std::declval<__type17>())) __type38;
    typedef decltype(std::declval<typename std::remove_cv<typename std::remove_reference<decltype(pythonic::numpy::functor::abs{})>::type>::type>()(std::declval<__type38>())) __type39;
    typedef container<typename std::remove_reference<__type39>::type> __type40;
    typedef typename __combined<__type9,__type40>::type __type41;
    typedef decltype(std::declval<typename std::remove_cv<typename std::remove_reference<decltype(pythonic::numpy::functor::max{})>::type>::type>()(std::declval<__type41>())) __type42;
    typedef decltype(std::declval<typename std::remove_cv<typename std::remove_reference<decltype(pythonic::__builtin__::functor::max{})>::type>::type>()(std::declval<__type10>(), std::declval<__type42>())) __type43;
    typedef decltype((std::declval<__type43>() + std::declval<__type10>())) __type45;
    typedef decltype((pythonic::operator_::div(std::declval<__type10>(), std::declval<__type45>()))) __type46;
    typedef decltype((std::declval<__type9>() * std::declval<__type46>())) __type47;
    typename pythonic::assignable<decltype(pythonic::__builtin__::getattr<pythonic::types::attr::SHAPE>(image))>::type __tuple0 = pythonic::__builtin__::getattr<pythonic::types::attr::SHAPE>(image);
    ;
    ;
    ;
    typename pythonic::assignable<typename __combined<__type9,__type46,__type47,__type40>::type>::type out_image = pythonic::numpy::functor::empty{}(pythonic::types::make_tuple((std::get<0>(__tuple0) - 2L), (std::get<1>(__tuple0) - 2L), std::get<2>(__tuple0)));
    out_image(pythonic::types::contiguous_slice(pythonic::__builtin__::None,pythonic::__builtin__::None),pythonic::types::contiguous_slice(pythonic::__builtin__::None,pythonic::__builtin__::None),pythonic::types::contiguous_slice(pythonic::__builtin__::None,pythonic::__builtin__::None)) = pythonic::numpy::functor::abs{}((((((4L * image(pythonic::types::contiguous_slice(1L,(-1L)),pythonic::types::contiguous_slice(1L,(-1L)),pythonic::types::contiguous_slice(pythonic::__builtin__::None,pythonic::__builtin__::None))) - image(pythonic::types::contiguous_slice(pythonic::__builtin__::None,(-2L)),pythonic::types::contiguous_slice(1L,(-1L)),pythonic::types::contiguous_slice(pythonic::__builtin__::None,pythonic::__builtin__::None))) - image(pythonic::types::contiguous_slice(2L,pythonic::__builtin__::None),pythonic::types::contiguous_slice(1L,(-1L)),pythonic::types::contiguous_slice(pythonic::__builtin__::None,pythonic::__builtin__::None))) - image(pythonic::types::contiguous_slice(1L,(-1L)),pythonic::types::contiguous_slice(pythonic::__builtin__::None,(-2L)),pythonic::types::contiguous_slice(pythonic::__builtin__::None,pythonic::__builtin__::None))) - image(pythonic::types::contiguous_slice(1L,(-1L)),pythonic::types::contiguous_slice(2L,pythonic::__builtin__::None),pythonic::types::contiguous_slice(pythonic::__builtin__::None,pythonic::__builtin__::None))));
    ;
    ;
    out_image *= (pythonic::operator_::div(1.0, (pythonic::__builtin__::functor::max{}(1.0, pythonic::numpy::functor::max{}(out_image)) + 1e-09)));
    return out_image;
  }
  template <typename argument_type0 >
  typename convolve_laplacien2::type<argument_type0>::result_type convolve_laplacien2::operator()(argument_type0 const & image) const
  {
    typedef typename pythonic::assignable<decltype(pythonic::__builtin__::getattr<pythonic::types::attr::SHAPE>(std::declval<typename std::remove_cv<typename std::remove_reference<argument_type0>::type>::type>()))>::type __type0;
    typedef typename std::tuple_element<0,typename std::remove_reference<__type0>::type>::type __type1;
    typedef long __type2;
    typedef decltype((std::declval<__type1>() - std::declval<__type2>())) __type3;
    typedef typename std::tuple_element<1,typename std::remove_reference<__type0>::type>::type __type4;
    typedef decltype((std::declval<__type4>() - std::declval<__type2>())) __type6;
    typedef decltype(pythonic::types::make_tuple(std::declval<__type3>(), std::declval<__type6>())) __type7;
    typedef typename pythonic::assignable<decltype(std::declval<typename std::remove_cv<typename std::remove_reference<decltype(pythonic::numpy::functor::empty{})>::type>::type>()(std::declval<__type7>()))>::type __type8;
    typedef double __type9;
    typedef typename std::remove_cv<typename std::remove_reference<argument_type0>::type>::type __type12;
    typedef pythonic::types::contiguous_slice __type13;
    typedef decltype(std::declval<__type12>()(std::declval<__type13>(), std::declval<__type13>())) __type15;
    typedef decltype((std::declval<__type2>() * std::declval<__type15>())) __type16;
    typedef decltype((std::declval<__type16>() - std::declval<__type15>())) __type20;
    typedef decltype((std::declval<__type20>() - std::declval<__type15>())) __type24;
    typedef decltype((std::declval<__type24>() - std::declval<__type15>())) __type28;
    typedef decltype((std::declval<__type28>() - std::declval<__type15>())) __type32;
    typedef decltype(std::declval<typename std::remove_cv<typename std::remove_reference<decltype(pythonic::numpy::functor::abs{})>::type>::type>()(std::declval<__type32>())) __type33;
    typedef container<typename std::remove_reference<__type33>::type> __type34;
    typedef typename __combined<__type8,__type34>::type __type35;
    typedef decltype(std::declval<typename std::remove_cv<typename std::remove_reference<decltype(pythonic::numpy::functor::max{})>::type>::type>()(std::declval<__type35>())) __type36;
    typedef decltype(std::declval<typename std::remove_cv<typename std::remove_reference<decltype(pythonic::__builtin__::functor::max{})>::type>::type>()(std::declval<__type9>(), std::declval<__type36>())) __type37;
    typedef decltype((std::declval<__type37>() + std::declval<__type9>())) __type39;
    typedef decltype((pythonic::operator_::div(std::declval<__type9>(), std::declval<__type39>()))) __type40;
    typedef decltype((std::declval<__type8>() * std::declval<__type40>())) __type41;
    typename pythonic::assignable<decltype(pythonic::__builtin__::getattr<pythonic::types::attr::SHAPE>(image))>::type __tuple0 = pythonic::__builtin__::getattr<pythonic::types::attr::SHAPE>(image);
    ;
    ;
    typename pythonic::assignable<typename __combined<__type8,__type40,__type41,__type34>::type>::type out_image = pythonic::numpy::functor::empty{}(pythonic::types::make_tuple((std::get<0>(__tuple0) - 2L), (std::get<1>(__tuple0) - 2L)));
    out_image(pythonic::types::contiguous_slice(pythonic::__builtin__::None,pythonic::__builtin__::None),pythonic::types::contiguous_slice(pythonic::__builtin__::None,pythonic::__builtin__::None)) = pythonic::numpy::functor::abs{}((((((4L * image(pythonic::types::contiguous_slice(1L,(-1L)),pythonic::types::contiguous_slice(1L,(-1L)))) - image(pythonic::types::contiguous_slice(pythonic::__builtin__::None,(-2L)),pythonic::types::contiguous_slice(1L,(-1L)))) - image(pythonic::types::contiguous_slice(2L,pythonic::__builtin__::None),pythonic::types::contiguous_slice(1L,(-1L)))) - image(pythonic::types::contiguous_slice(1L,(-1L)),pythonic::types::contiguous_slice(pythonic::__builtin__::None,(-2L)))) - image(pythonic::types::contiguous_slice(1L,(-1L)),pythonic::types::contiguous_slice(2L,pythonic::__builtin__::None))));
    ;
    ;
    out_image *= (pythonic::operator_::div(1.0, (pythonic::__builtin__::functor::max{}(1.0, pythonic::numpy::functor::max{}(out_image)) + 1e-09)));
    return out_image;
  }
  template <typename argument_type0 >
  typename convolve_mean3::type<argument_type0>::result_type convolve_mean3::operator()(argument_type0 const & image) const
  {
    typedef typename pythonic::assignable<decltype(pythonic::__builtin__::getattr<pythonic::types::attr::SHAPE>(std::declval<typename std::remove_cv<typename std::remove_reference<argument_type0>::type>::type>()))>::type __type0;
    typedef typename std::tuple_element<0,typename std::remove_reference<__type0>::type>::type __type1;
    typedef long __type2;
    typedef decltype((std::declval<__type1>() - std::declval<__type2>())) __type3;
    typedef typename std::tuple_element<1,typename std::remove_reference<__type0>::type>::type __type4;
    typedef decltype((std::declval<__type4>() - std::declval<__type2>())) __type6;
    typedef typename std::tuple_element<2,typename std::remove_reference<__type0>::type>::type __type7;
    typedef decltype(pythonic::types::make_tuple(std::declval<__type3>(), std::declval<__type6>(), std::declval<__type7>())) __type8;
    typedef typename pythonic::assignable<decltype(std::declval<typename std::remove_cv<typename std::remove_reference<decltype(pythonic::numpy::functor::empty{})>::type>::type>()(std::declval<__type8>()))>::type __type9;
    typedef double __type10;
    typedef typename std::remove_cv<typename std::remove_reference<argument_type0>::type>::type __type11;
    typedef pythonic::types::contiguous_slice __type12;
    typedef decltype(std::declval<__type11>()(std::declval<__type12>(), std::declval<__type12>(), std::declval<__type12>())) __type15;
    typedef decltype((std::declval<__type15>() + std::declval<__type15>())) __type20;
    typedef decltype((std::declval<__type20>() + std::declval<__type15>())) __type25;
    typedef decltype((std::declval<__type25>() + std::declval<__type15>())) __type30;
    typedef decltype((std::declval<__type10>() * std::declval<__type30>())) __type31;
    typedef container<typename std::remove_reference<__type31>::type> __type32;
    typename pythonic::assignable<decltype(pythonic::__builtin__::getattr<pythonic::types::attr::SHAPE>(image))>::type __tuple0 = pythonic::__builtin__::getattr<pythonic::types::attr::SHAPE>(image);
    ;
    ;
    ;
    typename pythonic::assignable<typename __combined<__type9,__type32>::type>::type out_image = pythonic::numpy::functor::empty{}(pythonic::types::make_tuple((std::get<0>(__tuple0) - 2L), (std::get<1>(__tuple0) - 2L), std::get<2>(__tuple0)));
    out_image(pythonic::types::contiguous_slice(pythonic::__builtin__::None,pythonic::__builtin__::None),pythonic::types::contiguous_slice(pythonic::__builtin__::None,pythonic::__builtin__::None),pythonic::types::contiguous_slice(pythonic::__builtin__::None,pythonic::__builtin__::None)) = (0.25 * (((image(pythonic::types::contiguous_slice(pythonic::__builtin__::None,(-2L)),pythonic::types::contiguous_slice(1L,(-1L)),pythonic::types::contiguous_slice(pythonic::__builtin__::None,pythonic::__builtin__::None)) + image(pythonic::types::contiguous_slice(2L,pythonic::__builtin__::None),pythonic::types::contiguous_slice(1L,(-1L)),pythonic::types::contiguous_slice(pythonic::__builtin__::None,pythonic::__builtin__::None))) + image(pythonic::types::contiguous_slice(1L,(-1L)),pythonic::types::contiguous_slice(pythonic::__builtin__::None,(-2L)),pythonic::types::contiguous_slice(pythonic::__builtin__::None,pythonic::__builtin__::None))) + image(pythonic::types::contiguous_slice(1L,(-1L)),pythonic::types::contiguous_slice(2L,pythonic::__builtin__::None),pythonic::types::contiguous_slice(pythonic::__builtin__::None,pythonic::__builtin__::None))));
    return out_image;
  }
  template <typename argument_type0 >
  typename convolve_mean2::type<argument_type0>::result_type convolve_mean2::operator()(argument_type0 const & image) const
  {
    typedef typename pythonic::assignable<decltype(pythonic::__builtin__::getattr<pythonic::types::attr::SHAPE>(std::declval<typename std::remove_cv<typename std::remove_reference<argument_type0>::type>::type>()))>::type __type0;
    typedef typename std::tuple_element<0,typename std::remove_reference<__type0>::type>::type __type1;
    typedef long __type2;
    typedef decltype((std::declval<__type1>() - std::declval<__type2>())) __type3;
    typedef typename std::tuple_element<1,typename std::remove_reference<__type0>::type>::type __type4;
    typedef decltype((std::declval<__type4>() - std::declval<__type2>())) __type6;
    typedef decltype(pythonic::types::make_tuple(std::declval<__type3>(), std::declval<__type6>())) __type7;
    typedef typename pythonic::assignable<decltype(std::declval<typename std::remove_cv<typename std::remove_reference<decltype(pythonic::numpy::functor::empty{})>::type>::type>()(std::declval<__type7>()))>::type __type8;
    typedef double __type9;
    typedef typename std::remove_cv<typename std::remove_reference<argument_type0>::type>::type __type10;
    typedef pythonic::types::contiguous_slice __type11;
    typedef decltype(std::declval<__type10>()(std::declval<__type11>(), std::declval<__type11>())) __type13;
    typedef decltype((std::declval<__type13>() + std::declval<__type13>())) __type17;
    typedef decltype((std::declval<__type17>() + std::declval<__type13>())) __type21;
    typedef decltype((std::declval<__type21>() + std::declval<__type13>())) __type25;
    typedef decltype((std::declval<__type9>() * std::declval<__type25>())) __type26;
    typedef container<typename std::remove_reference<__type26>::type> __type27;
    typename pythonic::assignable<decltype(pythonic::__builtin__::getattr<pythonic::types::attr::SHAPE>(image))>::type __tuple0 = pythonic::__builtin__::getattr<pythonic::types::attr::SHAPE>(image);
    ;
    ;
    typename pythonic::assignable<typename __combined<__type8,__type27>::type>::type out_image = pythonic::numpy::functor::empty{}(pythonic::types::make_tuple((std::get<0>(__tuple0) - 2L), (std::get<1>(__tuple0) - 2L)));
    out_image(pythonic::types::contiguous_slice(pythonic::__builtin__::None,pythonic::__builtin__::None),pythonic::types::contiguous_slice(pythonic::__builtin__::None,pythonic::__builtin__::None)) = (0.25 * (((image(pythonic::types::contiguous_slice(pythonic::__builtin__::None,(-2L)),pythonic::types::contiguous_slice(1L,(-1L))) + image(pythonic::types::contiguous_slice(2L,pythonic::__builtin__::None),pythonic::types::contiguous_slice(1L,(-1L)))) + image(pythonic::types::contiguous_slice(1L,(-1L)),pythonic::types::contiguous_slice(pythonic::__builtin__::None,(-2L)))) + image(pythonic::types::contiguous_slice(1L,(-1L)),pythonic::types::contiguous_slice(2L,pythonic::__builtin__::None))));
    return out_image;
  }
}
#include <pythonic/python/exception_handler.hpp>
#ifdef ENABLE_PYTHON_MODULE
typename __pythran_kernels::convolve_mean2::type<pythonic::types::ndarray<double,2>>::result_type convolve_mean20(pythonic::types::ndarray<double,2> image) 
{
  
                            PyThreadState *_save = PyEval_SaveThread();
                            try {
                                auto res = __pythran_kernels::convolve_mean2()(image);
                                PyEval_RestoreThread(_save);
                                return res;
                            }
                            catch(...) {
                                PyEval_RestoreThread(_save);
                                throw;
                            }
                            ;
}
typename __pythran_kernels::convolve_mean2::type<pythonic::types::numpy_texpr<pythonic::types::ndarray<double,2>>>::result_type convolve_mean21(pythonic::types::numpy_texpr<pythonic::types::ndarray<double,2>> image) 
{
  
                            PyThreadState *_save = PyEval_SaveThread();
                            try {
                                auto res = __pythran_kernels::convolve_mean2()(image);
                                PyEval_RestoreThread(_save);
                                return res;
                            }
                            catch(...) {
                                PyEval_RestoreThread(_save);
                                throw;
                            }
                            ;
}

static PyObject *
__pythran_wrap_convolve_mean20(PyObject *self, PyObject *args, PyObject *kw)
{
    PyObject* args_obj[1+1];
    char const* keywords[] = {"image", nullptr};
    if(! PyArg_ParseTupleAndKeywords(args, kw, "O",
                                     (char**)keywords, &args_obj[0]))
        return nullptr;
    if(is_convertible<pythonic::types::ndarray<double,2>>(args_obj[0]))
        return to_python(convolve_mean20(from_python<pythonic::types::ndarray<double,2>>(args_obj[0])));
    else {
        return nullptr;
    }
}

static PyObject *
__pythran_wrap_convolve_mean21(PyObject *self, PyObject *args, PyObject *kw)
{
    PyObject* args_obj[1+1];
    char const* keywords[] = {"image", nullptr};
    if(! PyArg_ParseTupleAndKeywords(args, kw, "O",
                                     (char**)keywords, &args_obj[0]))
        return nullptr;
    if(is_convertible<pythonic::types::numpy_texpr<pythonic::types::ndarray<double,2>>>(args_obj[0]))
        return to_python(convolve_mean21(from_python<pythonic::types::numpy_texpr<pythonic::types::ndarray<double,2>>>(args_obj[0])));
    else {
        return nullptr;
    }
}

            static PyObject *
            __pythran_wrapall_convolve_mean2(PyObject *self, PyObject *args, PyObject *kw)
            {
                return pythonic::handle_python_exception([self, args, kw]()
                -> PyObject* {

if(PyObject* obj = __pythran_wrap_convolve_mean20(self, args, kw))
    return obj;
PyErr_Clear();


if(PyObject* obj = __pythran_wrap_convolve_mean21(self, args, kw))
    return obj;
PyErr_Clear();

                PyErr_SetString(PyExc_TypeError,
                "Invalid argument type for pythranized function `convolve_mean2'.\n"
                "Candidates are:\n   convolve_mean2(ndarray<double,2>)\n   convolve_mean2(numpy_texpr<ndarray<double,2>>)\n"
                );
                return nullptr;
                });
            }


static PyMethodDef Methods[] = {
    {
    "convolve_mean2",
    (PyCFunction)__pythran_wrapall_convolve_mean2,
    METH_VARARGS | METH_KEYWORDS,
    "Supported prototypes:\n    - convolve_mean2(float64[][])\n    - convolve_mean2(float64[][].T)\n"},
    {NULL, NULL, 0, NULL}
};


#if PY_MAJOR_VERSION >= 3
  static struct PyModuleDef moduledef = {
    PyModuleDef_HEAD_INIT,
    "kernels",            /* m_name */
    "",         /* m_doc */
    -1,                  /* m_size */
    Methods,             /* m_methods */
    NULL,                /* m_reload */
    NULL,                /* m_traverse */
    NULL,                /* m_clear */
    NULL,                /* m_free */
  };
#define PYTHRAN_RETURN return theModule
#define PYTHRAN_MODULE_INIT(s) PyInit_##s
#else
#define PYTHRAN_RETURN return
#define PYTHRAN_MODULE_INIT(s) init##s
#endif
PyMODINIT_FUNC
PYTHRAN_MODULE_INIT(kernels)(void)
__attribute__ ((visibility("default")))
__attribute__ ((externally_visible));
PyMODINIT_FUNC
PYTHRAN_MODULE_INIT(kernels)(void) {
    #ifdef PYTHONIC_TYPES_NDARRAY_HPP
        import_array()
    #endif
    #if PY_MAJOR_VERSION >= 3
    PyObject* theModule = PyModule_Create(&moduledef);
    #else
    PyObject* theModule = Py_InitModule3("kernels",
                                         Methods,
                                         ""
    );
    #endif
    if(not theModule)
        PYTHRAN_RETURN;
    PyObject * theDoc = Py_BuildValue("(sss)",
                                      "0.8.3",
                                      "2017-11-09 11:33:30.052090",
                                      "9a349ecedd9ba3cb2c568c07df5c07bb0095188c3271daf753e0c430b214804c");
    if(not theDoc)
        PYTHRAN_RETURN;
    PyModule_AddObject(theModule,
                       "__pythran__",
                       theDoc);

    PYTHRAN_RETURN;
}

#endif