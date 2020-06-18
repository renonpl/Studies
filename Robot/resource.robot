*** Settings ***
Library           SeleniumLibrary
Library           Collections

*** Variables ***
${START}          file:${CURDIR}${/}page\\index.html
${home}           index.html
${gallery}        gallery.html
${news}           news.html
${contact}        contact.html

*** Keywords ***
Start Browser
    Open Browser    ${START}

Check List Length
    [Arguments]    ${list}    ${number}
    ${numList} =    Get Length    ${list}
    Should Be Equal As Integers    ${numList}    ${number}

Input Name
    [Arguments]    ${name}
    Input Text    name    ${name}

Input Surname
    [Arguments]    ${surname}
    Input Text    surname    ${surname}

Input Email
    [Arguments]    ${email}
    Input Text    email    ${email}

Select Country
    [Arguments]    ${number}
    Select From List By Index    country    ${number}

Fill About
    [Arguments]    ${text}
    Input Text    message    ${text}

Check If Empty Contact Form
    ${name}    Get Text    name
    Should Be Empty    ${name}
    ${surname}    Get Text    surname
    Should Be Empty    ${surname}
    ${email}    Get Text    email
    Should Be Empty    ${email}
    ${message}    Get Text    message
    Should Be Empty    ${message}

Fill In Contact Form
    Input Name    Jan
    Input Surname    Kowalski
    Input Email    jan_kowalski@kowalskie.pl
    Select Country    4
    Fill About    Hello there!

Print Source Files
    [Arguments]    ${list}
    FOR    ${el}    IN    @{list}
        Log    ${el.get_attribute('src')}
    END

Browse Sites
    [Arguments]    ${hrList}    ${altList}
    FOR    ${el}    ${alt}    IN ZIP    ${hrList}    ${altList}
        Log    ${el}
        Log    ${alt}
    END
    FOR    ${el}    ${alt}    IN ZIP    ${hrList}    ${altList}
        Go to    ${el}
        ${title}    Get Title
        Should Contain    ${title}    ${alt}    ignore_case=True
        Log    ${alt}
    END

Check Footer
    ${myLocat}=    Get Location
    ${list}=    Get WebElements    xpath: //footer[@class="footer"]//div[@class="container"]//a
    ${img}=    Get WebElements    xpath: //footer[@class="footer"]//div[@class="container"]//img
    ${href}=    Create List
    FOR    ${el}    IN    @{list}
        ${value}=    Get Element Attribute    ${el}    href
        Append To List    ${href}    ${value}
    END
    ${alts}=    Create List
    FOR    ${el}    IN    @{img}
        ${value}=    Get Element Attribute    ${el}    alt
        Append To List    ${alts}    ${value}
    END
    Browse Sites    ${href}    ${alts}
    Go to    ${myLocat}

Check Site
    [Arguments]    ${site}
    Click link    ${site}
    Check Footer
