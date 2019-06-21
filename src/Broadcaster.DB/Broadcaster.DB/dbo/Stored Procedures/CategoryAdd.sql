-- =============================================
-- Author:		Pedro Roque, High Precision
-- Create date: 2007-12-2008
-- Description:	Inserts a new Music Category, returning the new item ID
-- =============================================
CREATE PROCEDURE [dbo].[CategoryAdd]
	-- Add the parameters for the stored procedure here
	@Name char(100),
	@CategoryID int = 0 OUTPUT
AS
BEGIN
	INSERT INTO CATEGORIES ([Name],Activ) VALUES (@Name,1)

	SET @CategoryID = Scope_Identity()
END
