/*
*
* Copyright 2014 Telefonica Investigacion y Desarrollo, S.A.U
*
* This file is part of Orion Context Broker.
*
* Orion Context Broker is free software: you can redistribute it and/or
* modify it under the terms of the GNU Affero General Public License as
* published by the Free Software Foundation, either version 3 of the
* License, or (at your option) any later version.
*
* Orion Context Broker is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero
* General Public License for more details.
*
* You should have received a copy of the GNU Affero General Public License
* along with Orion Context Broker. If not, see http://www.gnu.org/licenses/.
*
* For those usages not covered by this license please contact with
* fermin at tid dot es
*
* Author: Ken Zangelin
*/
#include <string>
#include <vector>

#include "ngsi/ParseData.h"
#include "ngsi/EntityId.h"
#include "ngsi10/QueryContextRequest.h"
#include "rest/ConnectionInfo.h"
#include "rest/uriParamNames.h"
#include "serviceRoutines/getAllContextEntities.h"
#include "serviceRoutines/postQueryContext.h"



/* ****************************************************************************
*
* getAllContextEntities - 
*/
std::string getAllContextEntities
(
  ConnectionInfo*            ciP,
  int                        components,
  std::vector<std::string>&  compV,
  ParseData*                 parseDataP
)
{
  QueryContextRequest*  reqP   = &parseDataP->qcr.res;
  EntityId*             eP     = new EntityId(".*", "", "true");
  std::string           res;

  eP->type = ciP->uriParam[URI_PARAM_ENTITY_TYPE];

  reqP->entityIdVector.push_back(eP);

  res = postQueryContext(ciP, components, compV, parseDataP);
  delete eP;

  return res;
}