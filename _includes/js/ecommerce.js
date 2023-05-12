function reportPurchase(transaction) {
  plausible('Purchase', {
    props: { total: transaction.total, currency: transaction.currency }
  })
}
