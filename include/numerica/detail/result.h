#pragma once

#include <cstdint>
#include <stdexcept>

namespace numerica::detail {

enum class status : std::uint8_t {
  ok = 0,
  invalid_argument,
  non_finite_eval,
  max_iter,
  domain_error
};

constexpr const char *to_string(status s) noexcept {
  switch (s) {
  case status::ok:
    return "ok";
  case status::invalid_argument:
    return "invalid argument";
  case status::non_finite_eval:
    return "non_finite_eval";
  case status::max_iter:
    return "max iter";
  case status::domain_error:
    return "domain error";
  default:
    return "unknown";
  }
}

struct result_meta {
  status code = status::ok;
  int iters = 0;
  int evals = 0;
}
// TODO: update descriptions + write tests

} // namespace numerica::detail
