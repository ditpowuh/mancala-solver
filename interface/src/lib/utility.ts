export function getDefaultBoard() {
  return Array.from({length: 14}, function (_, index) {
    if (index === 6 || index === 13) {
      return 0;
    }
    else {
      return 4;
    }
  });
}
