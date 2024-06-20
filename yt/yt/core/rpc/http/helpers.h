#pragma once

#include "public.h"

namespace NYT::NRpc::NHttp {

////////////////////////////////////////////////////////////////////////////////

TString ToHttpContentType(EMessageFormat format);
std::optional<EMessageFormat> FromHttpContentType(TStringBuf contentType);

////////////////////////////////////////////////////////////////////////////////

} // namespace NYT::NRpc::NHttp
