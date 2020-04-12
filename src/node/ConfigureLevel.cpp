#include "ConfigureLevel.h"

#include "log_for_logger.h"
ENABLE_LOG(INFO);

Node * ConfigureLevel::SearchNodeWithName::visit(Node *node) {
  return static_cast<LogNode *>(node)->hasSameName(_nameToSearch)?node:NULL;
}

bool ConfigureLevel::SetLevel::visit(Node *node) {
  LogNode *logNode = static_cast<LogNode *>(node);
  LOG_ENTER_("%s:%d", logNode->_name, _level);
  logNode->_logLevel = _level;
  return true;
}


















