<?php
// $Id$

/**
 * @file
 * Token hooks.
 */

/**
 * Implement hook_token_info().
 */
function uc_payment_token_info() {
  $order['payment-method'] = array(
    'name' => t('Payment method'),
    'description' => t('The payment method of the order.'),
  );
  $order['payment-balance'] = array(
    'name' => t('Balance'),
    'description' => t('The payment balance of the order'),
  );

  return array(
    'tokens' => array('uc_order' => $order),
  );
}

/**
 * Implement hook_tokens().
 */
function uc_payment_tokens($type, $tokens, $data = array(), $options = array()) {
  $values = array();

  if ($type == 'uc_order' && !empty($data['uc_order'])) {
    $order = $data['uc_order'];

    if (isset($tokens['payment-method'])) {
      $original = $tokens['payment-method'];
      $values[$original] = _uc_payment_method_data($order->payment_method, 'review');
      if (empty($values[$original])) {
        $values[$original] = _uc_payment_method_data($order->payment_method, 'name');
      }
    }

    if (isset($tokens['payment-balance'])) {
      $original = $tokens['payment-method'];
      $context = array(
        'revision' => 'formatted',
        'type' => 'amount',
      );
      $values[$original] = uc_price(uc_payment_balance($order), $context);
    }
  }

  return $values;
}
