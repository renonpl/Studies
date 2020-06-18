*** Settings ***
Library           SeleniumLibrary
Resource          resource.robot
Library           myStringLib.py

*** Test Cases ***
test1
    Start Browser
    ${title}    Get Title
    ${maxChar}    Find Max Char    ${title}
    Should Be Equal    ${maxChar}    o
    ${stringValue}    Sum Char Value    ${title}
    Should Be Equal As Integers    ${stringValue}    393
    Click Link    ${news}
    ${title}    Get Title
    ${maxChar}    Find Max Char    ${title}
    Should Be Equal    ${maxChar}    w
    ${stringValue}    Sum Char Value    ${title}
    Should Be Equal As Integers    ${stringValue}    413
    [Teardown]	Close Browser
