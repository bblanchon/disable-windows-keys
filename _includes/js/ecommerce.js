function reportPurchase(transaction) {
  dataLayer.push({
    'event': 'generic',
    'eventCategory': 'ecommerce',
    'eventAction': 'purchase',
    'eventLabel': transaction.buyer,
    'eventValue': parseInt(transaction.total)
  })
  plausible('Purchase', {
    props: { total: transaction.total, currency: transaction.currency }
  })
}
