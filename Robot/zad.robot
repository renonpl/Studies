*** Settings ***
Test Setup        Start Browser
Test Teardown     Close Browser
Library           SeleniumLibrary
Resource          resource.robot

*** Test Cases ***
test1
    Click Element    id=new_window_button
    Title Should Be    Home
    @{windows} =    Get Window Names
    Check List Length    ${windows}    2

test2
    Click link    ${contact}
    Wait Until Page Contains Element    id=contact_form
    Check If Empty Contact Form
    Fill In Contact Form
    Submit Form    contact_form
    Alert Should Be Present

test3
    Click Link    ${gallery}
    ${images}    Get WebElements    class=gallery
    Check List Length    ${images}    11
    Print Source Files    ${images}
    Sleep    2

test4
    [Template]    Check Site
    ${home}
    ${news}
    ${gallery}
    ${contact}
