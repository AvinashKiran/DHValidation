//
//  DHValidation.h
//  ceol
//
//  Created by Ben McRedmond on 24/05/2009.
//  Copyright 2009 Ben McRedmond. All rights reserved.
//

#import <Cocoa/Cocoa.h>

extern NSString * const DHValidateAlpha;
extern NSString * const DHValidateAlphaSpaces;
extern NSString * const DHValidateAlphaNumeric;
extern NSString * const DHValidateAlphaNumericDash;
extern NSString * const DHValidateNotEmpty;
extern NSString * const DHValidateEmail;
extern NSString * const DHValidateMatchesConfirmation;
extern NSString * const DHValidateMinimumLength;
extern NSString * const DHValidateCustomAsync;

@protocol DHValidationDelegate  <NSObject>
@optional
- (void) updateErrorField: (NSTextField *) errorField withErrors: (NSArray *) errors;
@end

@interface DHValidation : NSObject {
    NSMutableDictionary *errorTable;
    NSMutableDictionary *errorStrings;
    
    NSMutableDictionary *asyncErrorFields;
    BOOL asyncInProgress;
    
    NSString *currentTag;
    NSTextField *currentErrorField;
    
    id delegate;
    
    // Variables for this validation only
    NSMutableArray *tempErrors;
}

@property (assign) id <DHValidationDelegate> delegate;
@property (readonly) BOOL asyncInProgress;

- (id) initWithErrorMessages: (NSDictionary *) errors;

- (NSArray *) validateObject: (id) object tag: (NSString *) tag errorField: (NSTextField *) errorField rules: (NSString * const) firstRule, ... NS_REQUIRES_NIL_TERMINATION;
- (NSArray *) validateObjectWithParamaters: (id) object tag: (NSString *) tag errorField: (NSTextField *) errorField rules: (id) firstRule, ... NS_REQUIRES_NIL_TERMINATION;
- (void) validateRule: (NSString * const) rule candidate: (id) candidate tag: (NSString *) tag;
- (void) validateRuleWithParamater: (NSString * const) rule candidate: (id) candidate tag: (NSString *) tag paramater: (id) paramater;
- (void) modifyErrorTable: (NSString *) tag method: (NSString * const) method isValid: (BOOL) isValid;
- (int) errorCount;
- (int) errorCountForTag: (NSString *) tag;
- (void) reset;

// Delegates
- (void) updateErrorFieldDelegate:errorField withErrors:errors;

// Basic Validators
- (BOOL) validateAlpha: (NSString *) candidate;
- (BOOL) validateAlphaSpaces: (NSString *) candidate;
- (BOOL) validateAlphanumeric: (NSString *) candidate;
- (BOOL) validateAlphanumericDash: (NSString *) candidate;
- (BOOL) validateStringInCharacterSet: (NSString *) string characterSet: (NSMutableCharacterSet *) characterSet;
- (BOOL) validateNotEmpty: (NSString *) candidate;
- (BOOL) validateEmail: (NSString *) candidate;

// Complex validators (requires second paramater)
- (BOOL) validateMatchesConfirmation: (NSString *) candidate paramater: (NSString *) confirmation;
- (BOOL) validateMinimumLength: (NSString *) candidate paramater: (int) length;
- (void) asyncValidationMethod: (id) candidate paramater: (NSArray *) objectAndSelector;
- (void) asyncValidationMethodComplete: (NSString *) tag isValid: (BOOL) isValid error: (NSString *) error;
    
@end