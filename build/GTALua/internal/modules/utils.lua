-- Utils
utils = {}

function utils.IsInArray(table, search)
  for _, v in pairs(table) do
    if v == search then
      return true
    end
  end
  return false
end
