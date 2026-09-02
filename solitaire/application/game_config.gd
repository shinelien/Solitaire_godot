class_name GameConfig
extends RefCounted

## Static configuration: deal library paths, counts, hashes (source-bound),
## and gameplay limits.

const DEAL_PATH_1 := "res://data/legacy/bureau1.d"
const DEAL_PATH_3 := "res://data/legacy/bureau3.d"

const EXPECTED_COUNT_1 := 32084
const EXPECTED_COUNT_3 := 4999
const EXPECTED_BYTES_1 := 1700452
const EXPECTED_BYTES_3 := 264947

const SHA256_1 := "36414bfcd91c916caa77c8b908dc51000732bfc8ba2b8113798d6a2a48d2ccf5"
const SHA256_3 := "0bf9409ac5a5954a02460274fc50e8cd1ca79693be4dd90e70cc6ebcac81ca43"

const DRAW1 := 1
const DRAW3 := 3

const MAX_UNDO := 200
const AUTO_COMPLETE_LIMIT := 60
