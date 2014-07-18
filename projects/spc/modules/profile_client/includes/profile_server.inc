<?php

class ServiceConnection {

  protected $url;
  protected $login_data;

  public function __construct() {
    $this->url = variable_get('domain') . '/' . variable_get('endpoint');
    $this->login_data = $this->login();
  }

  protected function setOptions($login_data, $method, $data = NULL) {
    $options = array(
      'headers' => array(
        'Content-Type' => 'application/json',
        'Cookie' => $login_data['cookie'],
        'X-CSRF-Token' => $login_data['token'],
      ),
      'method' => $method,
    );
    if ($data) {
      $options['data'] = $data;
    }
    return $options;
  }

  protected function login() {
    if (variable_get('kill_cookie')) {
      unset($_COOKIE);
      dsm('kill_cookie');
    }
    if (isset($_COOKIE['drupal_session_name']) && isset($_COOKIE['drupal_session_id']) && isset($_COOKIE['drupal_session_token'])) {
      $cookie = '' . $_COOKIE['drupal_session_name'] . '=' . $_COOKIE['drupal_session_id'] . '';
      return array('cookie' => $cookie, 'token' => $_COOKIE['drupal_session_token']);
    }
    else {
      $login_url = $this->url . '/user/login';
      $user_data = array(
        'username' => variable_get('user'),
        'password' => variable_get('password'),
      );
      $user_options = array(
        'headers' => array(
          'Content-Type' => 'application/json'),
        'method' => 'POST',
        'data' => json_encode($user_data),
      );
    };
    $result = drupal_http_request($login_url, $user_options);
    if ($result->code == 200) {
      $user_data = json_decode($result->data);
      setcookie('drupal_session_name', $user_data->session_name);
      setcookie('drupal_session_id', $user_data->sessid);
      $cookie = '' . $user_data->session_name . '=' . $user_data->sessid . '';
      $token_options = array(
        'headers' => array(
          'Cookie' => $cookie,
        ),
        'method' => 'GET',
      );
      $token = drupal_http_request(variable_get('domain') . '/services/session/token', $token_options);
      setcookie('drupal_session_token', $token->data);
      return array('cookie' => $cookie, 'token' => $token->data);
    }
    else
      return FALSE;
  }

}

class CentralProfile extends ServiceConnection {

  public function fetch($param, $value) {
//    $url = "{$this->url}/user/1";
    $url = "{$this->url}/user?parameters[{$param}]=${value}";
    $options = $this->setOptions($this->login_data, 'GET');
    return drupal_http_request($url, $options);
  }

  public function create() {
    $url = "{$this->url}/user";


    $node_type = 'article';
    $node_title = 'Node updated: ' . date('c');
    $node_body = 'Node body';
    $node_format = 'filtered_html';

    $user_data = array(
      'name' => 'test',
      'first_name' => 'boris',
      'last_name' => 'doesborg',
    );
    $options = $this->setOptions($this->login_data, 'POST', json_encode($user_data));


    return drupal_http_request($url, $options);
  }

//  public function users() {
//    $url = "{$this->url}/user";
//    $options = $this->setOptions($this->login_data, 'GET');
//    return drupal_http_request($url, $options);
//  }
//    public function updated_users($timestamp) {
//    $url = "{$this->url}/updated_users/retrieve";
//    $options = $this->setOptions($this->login_data, 'GET');
//    return drupal_http_request($url, $options);
//  }

  public function updated_users($timestamp) {
    $url = "{$this->url}/user?parameters[]";
    $options = $this->setOptions($this->login_data, 'GET');
    return drupal_http_request($url, $options);
  }

}

class CentralArticle extends ServiceConnection {

  public function articles() {
    $url = "{$this->url}/blogs/retrieve?nitems=3&since=10";
    $options = $this->setOptions($this->login_data, 'GET');
    return drupal_http_request($url, $options);
  }

}
