### GetCount
> [!Note]
> For most code, this check will be performant. When using file formats
> where the cost of attribute reading is high and the time sampled array
> will be read into memory later, it may be better to explicitly read the
> value once and check the size of the array directly.
