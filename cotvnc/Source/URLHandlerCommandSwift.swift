//
//  URLHandlerCommandSwift.swift
//  Chicken
//
//  Created by C.W. Betts on 9/23/24.
//

import Foundation

@objc(URLHandlerCommand)
public class URLHandlerCommand : NSScriptCommand {
    
    private func scriptError(_ errorNumber: Int, description: String) {
        scriptErrorNumber = errorNumber
        scriptErrorString = description
    }
    
    /// Perform somewhat redundant checks here.
    /// The `NSScriptClassDescription` should do this as well, but there may be
    /// pathological cases where it is unable to do so, someone has modified
    /// the script suite, etc.
    public override func performDefaultImplementation() -> Any? {
        RFBConnectionManager.shared.launchedByURL = true
        
        let command = self.commandDescription.commandName
        let verb: String
        let urlString: String?
        
        // XXX should be read from .scriptTerminology, but Cocoa provides no way to do this
        if command == "GetURL" {
            verb = "get URL"
            urlString = self.directParameter as? String
        } else if command == "OpenURL" {
            verb = "open URL"
            urlString = self.directParameter as? String
        } else {
            scriptError(errAEEventNotHandled, description: String(format: "HostLauncher does not respond to R%@S.", command))
            return nil
        }
        
        // XXX should ignore arguments instead, if the GURL/OURL is coming from a Web browser?
        guard let arguments = self.arguments, !arguments.isEmpty else {
            scriptError(errAEParamMissed, description: "Cannot handle arguments for \(verb)")
            return nil
        }
        guard let urlString else {
            scriptError(errAEParamMissed, description: "No URL to open was specified.")
            return nil
        }
        
        // XXX CFURLCreateStringByAddingPercentEscapes is more permissive
        // wrt URL formats; may want to use it instead (see release notes)
        guard let url = URL(string: urlString) else {
            scriptError(kURLInvalidURLError, description: "URL format is invalid; must be fully qualified (scheme://host...).")
            return nil
        }
        
        let viewCtrlr = ServerDataViewController(releaseOnCloseOrConnect: ())
        
        RFBConnectionManager.shared.launchedByURL = true

        let server = ServerStandAlone()
        server.host = url.host
        
        if let portNumber = url.port {
            server.port = Int32(portNumber)
        }
        server.password = url.password
        
        viewCtrlr.server = server
        viewCtrlr.window?.makeKeyAndOrderFront(self)
        
        return nil
    }
}
