#if canImport(ExecUsd)
import ExecUsd
#else
import OpenUSD
#endif

public typealias ExecUsdSystem = Pixar.ExecUsdSystem

public extension ExecUsd
{
  typealias System = ExecUsdSystem
}

public extension ExecUsd.System
{
	
}