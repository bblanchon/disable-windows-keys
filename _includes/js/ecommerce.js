function reportPurchase(transaction) {
  dataLayer.push({
    'event': 'generic',
    'eventCategory': 'ecommerce',
    'eventAction': 'purchase',
    'eventLabel': transaction.buyer,
    'eventValue': parseInt(transaction.total)
  })
}
