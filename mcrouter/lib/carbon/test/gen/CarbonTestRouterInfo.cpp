/*
 *  Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 *  This source code is licensed under the MIT license found in the LICENSE
 *  file in the root directory of this source tree.
 *
 */

/*
 *  THIS FILE IS AUTOGENERATED. DO NOT MODIFY IT; ALL CHANGES WILL BE LOST IN
 *  VAIN.
 *
 *  @generated
 */
#include "CarbonTestRouterInfo.h"

#include <unordered_map>

#include <folly/Range.h>
#include <folly/dynamic.h>

#include <mcrouter/routes/ExtraRouteHandleProviderIf.h>
#include <mcrouter/routes/McRouteHandleProvider.h>

#include <mcrouter/lib/routes/NullRoute.h>
#include <mcrouter/routes/AllAsyncRouteFactory.h>
#include <mcrouter/routes/AllFastestRouteFactory.h>
#include <mcrouter/routes/AllInitialRouteFactory.h>
#include <mcrouter/routes/AllMajorityRouteFactory.h>
#include <mcrouter/routes/AllSyncRouteFactory.h>
#include <mcrouter/routes/BigValueRoute.h>
#include <mcrouter/routes/BlackholeRoute.h>
#include <mcrouter/routes/DevNullRoute.h>
#include <mcrouter/routes/ErrorRoute.h>
#include <mcrouter/routes/FailoverRoute.h>
#include <mcrouter/routes/HashRouteFactory.h>
#include <mcrouter/routes/HostIdRouteFactory.h>
#include <mcrouter/routes/LatencyInjectionRoute.h>
#include <mcrouter/routes/LatestRoute.h>
#include <mcrouter/routes/LoadBalancerRoute.h>
#include <mcrouter/routes/LoggingRoute.h>
#include <mcrouter/routes/MigrateRouteFactory.h>
#include <mcrouter/routes/MissFailoverRoute.h>
#include <mcrouter/routes/ModifyKeyRoute.h>
#include <mcrouter/routes/OperationSelectorRoute.h>
#include <mcrouter/routes/OutstandingLimitRoute.h>
#include <mcrouter/routes/RandomRouteFactory.h>

#include <mcrouter/routes/McExtraRouteHandleProvider.h>

using namespace facebook::memcache;
using namespace facebook::memcache::mcrouter;

namespace facebook {
namespace memcache {
namespace mcrouter {

extern template carbon::test::CarbonTestRouterInfo::RouteHandlePtr
makeAllAsyncRoute<carbon::test::CarbonTestRouterInfo>(
RouteHandleFactory<carbon::test::CarbonTestRouterInfo::RouteHandleIf>& factory,
const folly::dynamic& json);

extern template carbon::test::CarbonTestRouterInfo::RouteHandlePtr
makeAllFastestRoute<carbon::test::CarbonTestRouterInfo>(
RouteHandleFactory<carbon::test::CarbonTestRouterInfo::RouteHandleIf>& factory,
const folly::dynamic& json);

extern template carbon::test::CarbonTestRouterInfo::RouteHandlePtr
makeAllInitialRoute<carbon::test::CarbonTestRouterInfo>(
RouteHandleFactory<carbon::test::CarbonTestRouterInfo::RouteHandleIf>& factory,
const folly::dynamic& json);

extern template carbon::test::CarbonTestRouterInfo::RouteHandlePtr
makeAllMajorityRoute<carbon::test::CarbonTestRouterInfo>(
RouteHandleFactory<carbon::test::CarbonTestRouterInfo::RouteHandleIf>& factory,
const folly::dynamic& json);

extern template carbon::test::CarbonTestRouterInfo::RouteHandlePtr
makeAllSyncRoute<carbon::test::CarbonTestRouterInfo>(
RouteHandleFactory<carbon::test::CarbonTestRouterInfo::RouteHandleIf>& factory,
const folly::dynamic& json);

extern template carbon::test::CarbonTestRouterInfo::RouteHandlePtr
makeBigValueRoute<carbon::test::CarbonTestRouterInfo>(
RouteHandleFactory<carbon::test::CarbonTestRouterInfo::RouteHandleIf>& factory,
const folly::dynamic& json);

extern template carbon::test::CarbonTestRouterInfo::RouteHandlePtr
makeBlackholeRoute<carbon::test::CarbonTestRouterInfo>(
RouteHandleFactory<carbon::test::CarbonTestRouterInfo::RouteHandleIf>& factory,
const folly::dynamic& json);

extern template carbon::test::CarbonTestRouterInfo::RouteHandlePtr
makeDevNullRoute<carbon::test::CarbonTestRouterInfo>(
RouteHandleFactory<carbon::test::CarbonTestRouterInfo::RouteHandleIf>& factory,
const folly::dynamic& json);

extern template carbon::test::CarbonTestRouterInfo::RouteHandlePtr
makeErrorRoute<carbon::test::CarbonTestRouterInfo>(
RouteHandleFactory<carbon::test::CarbonTestRouterInfo::RouteHandleIf>& factory,
const folly::dynamic& json);

extern template carbon::test::CarbonTestRouterInfo::RouteHandlePtr
makeHashRoute<carbon::test::CarbonTestRouterInfo>(
RouteHandleFactory<carbon::test::CarbonTestRouterInfo::RouteHandleIf>& factory,
const folly::dynamic& json);

extern template carbon::test::CarbonTestRouterInfo::RouteHandlePtr
makeHostIdRoute<carbon::test::CarbonTestRouterInfo>(
RouteHandleFactory<carbon::test::CarbonTestRouterInfo::RouteHandleIf>& factory,
const folly::dynamic& json);

extern template carbon::test::CarbonTestRouterInfo::RouteHandlePtr
makeLatencyInjectionRoute<carbon::test::CarbonTestRouterInfo>(
RouteHandleFactory<carbon::test::CarbonTestRouterInfo::RouteHandleIf>& factory,
const folly::dynamic& json);

extern template carbon::test::CarbonTestRouterInfo::RouteHandlePtr
makeLatestRoute<carbon::test::CarbonTestRouterInfo>(
RouteHandleFactory<carbon::test::CarbonTestRouterInfo::RouteHandleIf>& factory,
const folly::dynamic& json);

extern template carbon::test::CarbonTestRouterInfo::RouteHandlePtr
makeLoadBalancerRoute<carbon::test::CarbonTestRouterInfo>(
RouteHandleFactory<carbon::test::CarbonTestRouterInfo::RouteHandleIf>& factory,
const folly::dynamic& json);

extern template carbon::test::CarbonTestRouterInfo::RouteHandlePtr
makeLoggingRoute<carbon::test::CarbonTestRouterInfo>(
RouteHandleFactory<carbon::test::CarbonTestRouterInfo::RouteHandleIf>& factory,
const folly::dynamic& json);

extern template carbon::test::CarbonTestRouterInfo::RouteHandlePtr
makeMigrateRoute<carbon::test::CarbonTestRouterInfo>(
RouteHandleFactory<carbon::test::CarbonTestRouterInfo::RouteHandleIf>& factory,
const folly::dynamic& json);

extern template carbon::test::CarbonTestRouterInfo::RouteHandlePtr
makeMissFailoverRoute<carbon::test::CarbonTestRouterInfo>(
RouteHandleFactory<carbon::test::CarbonTestRouterInfo::RouteHandleIf>& factory,
const folly::dynamic& json);

extern template carbon::test::CarbonTestRouterInfo::RouteHandlePtr
makeModifyKeyRoute<carbon::test::CarbonTestRouterInfo>(
RouteHandleFactory<carbon::test::CarbonTestRouterInfo::RouteHandleIf>& factory,
const folly::dynamic& json);

extern template carbon::test::CarbonTestRouterInfo::RouteHandlePtr
makeOperationSelectorRoute<carbon::test::CarbonTestRouterInfo>(
RouteHandleFactory<carbon::test::CarbonTestRouterInfo::RouteHandleIf>& factory,
const folly::dynamic& json);

extern template carbon::test::CarbonTestRouterInfo::RouteHandlePtr
makeRandomRoute<carbon::test::CarbonTestRouterInfo>(
RouteHandleFactory<carbon::test::CarbonTestRouterInfo::RouteHandleIf>& factory,
const folly::dynamic& json);

extern template class ExtraRouteHandleProviderIf<carbon::test::CarbonTestRouterInfo>;

} // namespace mcrouter
} // namespace memcache
} // namespace facebook

namespace carbon {
namespace test {

constexpr const char* CarbonTestRouterInfo::name;

/* static */ CarbonTestRouterInfo::RouteHandleFactoryMap
CarbonTestRouterInfo::buildRouteMap() {
  RouteHandleFactoryMap map{
      {"AllAsyncRoute", &makeAllAsyncRoute<CarbonTestRouterInfo>},
      {"AllFastestRoute", &makeAllFastestRoute<CarbonTestRouterInfo>},
      {"AllInitialRoute", &makeAllInitialRoute<CarbonTestRouterInfo>},
      {"AllMajorityRoute", &makeAllMajorityRoute<CarbonTestRouterInfo>},
      {"AllSyncRoute", &makeAllSyncRoute<CarbonTestRouterInfo>},
      {"BigValueRoute", &makeBigValueRoute<CarbonTestRouterInfo>},
      {"BlackholeRoute", &makeBlackholeRoute<CarbonTestRouterInfo>},
      {"DevNullRoute", &makeDevNullRoute<CarbonTestRouterInfo>},
      {"ErrorRoute", &makeErrorRoute<CarbonTestRouterInfo>},
      {"HashRoute",
       [](RouteHandleFactory<RouteHandleIf>& factory,
          const folly::dynamic& json) {
         return makeHashRoute<CarbonTestRouterInfo>(factory, json);
       }},
      {"HostIdRoute", &makeHostIdRoute<CarbonTestRouterInfo>},
      {"LatencyInjectionRoute",
       &makeLatencyInjectionRoute<CarbonTestRouterInfo>},
      {"LatestRoute", &makeLatestRoute<CarbonTestRouterInfo>},
      {"LoadBalancerRoute", &makeLoadBalancerRoute<CarbonTestRouterInfo>},
      {"LoggingRoute", &makeLoggingRoute<CarbonTestRouterInfo>},
      {"MigrateRoute", &makeMigrateRoute<CarbonTestRouterInfo>},
      {"MissFailoverRoute", &makeMissFailoverRoute<CarbonTestRouterInfo>},
      {"ModifyKeyRoute", &makeModifyKeyRoute<CarbonTestRouterInfo>},
      {"NullRoute", &makeNullRoute<CarbonTestRouteHandleIf>},
      {"OperationSelectorRoute",
       &makeOperationSelectorRoute<CarbonTestRouterInfo>},
      {"RandomRoute", &makeRandomRoute<CarbonTestRouterInfo>},
  };
  return map;
}

/* static */ CarbonTestRouterInfo::RouteHandleFactoryMapWithProxy
CarbonTestRouterInfo::buildRouteMapWithProxy() {
  return RouteHandleFactoryMapWithProxy();
}

/* static */ CarbonTestRouterInfo::RouteHandleFactoryMapForWrapper
CarbonTestRouterInfo::buildRouteMapForWrapper() {
  return RouteHandleFactoryMapForWrapper();
}

/* static */ bool CarbonTestRouterInfo::isSRLinked() {
    return false;
}
    
} // namespace test
} // namespace carbon
